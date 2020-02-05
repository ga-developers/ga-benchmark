# Copyright(C) ga-developers
#
# Repository: https://github.com/ga-developers/ga-benchmark.git
#
# This file is part of the GA-Benchmark project.
#
# GA-Benchmark is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# GA-Benchmark is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GA-Benchmark. If not, see <https://www.gnu.org/licenses/>.

import argparse, functools, os, json, shutil, sys
import numpy as np
import matplotlib.colors as colors
import matplotlib.pyplot as plt
from datetime import datetime
from tqdm import tqdm
from typing import Tuple

_COMPILER_ID_TO_NAME = {  # Source: https://cmake.org/cmake/help/v3.16/variable/CMAKE_LANG_COMPILER_ID.html
    'Absoft': 'Absoft Fortran',
    'ADSP': 'Analog VisualDSP++',
    'AppleClang': 'Apple Clang',
    'ARMCC': 'ARM Compiler',
    'ARMClang': 'ARM Compiler based on Clang',
    'Bruce': 'Bruce C Compiler',
    'CCur': 'Concurrent Fortran',
    'Clang': 'LLVM Clang',
    'Cray': 'Cray Compiler',
    'Embarcadero': 'Embarcadero',
    'Borland': 'Embarcadero',
    'Flang': 'Flang LLVM Fortran Compiler',
    'G95': 'G95 Fortran',
    'GNU': 'GNU Compiler Collection',
    'GHS': 'Green Hills Software',
    'HP': 'Hewlett-Packard Compiler',
    'IAR': 'IAR Systems',
    'Intel': 'Intel Compiler',
    'MSVC': 'Microsoft Visual Studio',
    'NVIDIA': 'NVIDIA CUDA Compiler',
    'OpenWatcom': 'Open Watcom',
    'PGI': 'The Portland Group',
    'PathScale': 'PathScale',
    'SDCC': 'Small Device C Compiler',
    'SunPro': 'Oracle Solaris Studio',
    'TI': 'Texas Instruments',
    'TinyCC': 'Tiny C Compiler',
    'XL': 'IBM XL',
    'VisualAge': 'IBM XL',
    'zOS': 'IBM XL',
    'XLClang': 'IBM Clang-based XL',
}

MESSAGES = {
    'MISSING_DATA': {
        'description': 'Missing Data',
        'short_description': 'Missing Data',
        'priority': 24.0 * 60 * 60 * 1000  # Milisseconds in one day (much more than the TIMEOUT value in CMake)
    },
    'IMPLEMENTED': {
        'description': 'Implemented',
        'short_description': 'Implemented',
        'priority': 0.0
    },
    'OPERATION_NOT_IMPLEMENTED': {
        'description': 'Operation not Implemented',
        'short_description': 'Operation not Implemented',
        'priority': -1.0
    },
    'MODEL_NOT_IMPLEMENTED': {
        'description': 'Model not Implemented',
        'short_description': 'Model not Implemented',
        'priority': -2.0
    },
    'OPERATION_LEADS_TO_COMPILATION_ERROR': {
        'description': 'Operation Leads to Compilation Error',
        'short_description': 'Compilation Error',
        'priority': -3.0
    },
    'OPERATION_LEADS_TO_RUNTIME_ERROR': {
        'description': 'Operation Leads to Runtime Error',
        'short_description': 'Runtime Error',
        'priority': -4.0
    }
}

_MESSAGE_PRIORITY_TO_KEY = {message_data['priority']: message_key for message_key, message_data in MESSAGES.items()}

METRICS = {
    'cpu_time': {'description': 'CPU time'},
    'real_time': {'description': 'Wall-clock time'}
}

MODELS = {
    'ConformalModel': {
        'description': 'Conformal',
        'id': 0x01
    },
    'EuclideanModel': {
        'description': 'Euclidean',
        'id': 0x02
    },
    'HomogeneousModel': {
        'description': 'Homogeneous',
        'id': 0x03
    },
    'MinkowskiModel': {
        'description': 'Minkowski',
        'id': 0x04
    }
}

_MODEL_ID_TO_KEY = {model_data['id']: model_key for model_key, model_data in MODELS.items()}

OPERATIONS = {
    'Algorithms': {
        'description': 'Algorithms',
        'arguments': {
        },
        'subgroups': {
            'Miscellaneous': {
                'description': 'Miscellaneous',
                'operations': {
                    'InverseKinematics': {'description': 'Inverse Kinematics'}
                }
            }
        }
    },
    'BinaryOperations': {
        'description': 'Binary Operations',
        'arguments': {
            'LeftGrade': {'description': 'LHS Grade'},
            'RightGrade': {'description': 'RHS Grade'}
        },
        'subgroups': {
            'GeometricProducts': {
                'description': 'Main Products',
                'operations': {
                    'CommutatorProduct': {'description': 'Commutator Product'},
                    'GeometricProduct': {'description': 'Geometric Product'},
                    'InverseGeometricProduct': {'description': 'Inverse Geometric Product'}
                }
            },
            'InnerProducts': {
                'description': 'Inner Products',
                'operations': {
                    'DotProduct': {'description': 'Dot Product'},
                    'HestenesInnerProduct': {'description': 'Hestenes\' Inner Product'},
                    'LeftContraction': {'description': 'Left Contraction'},
                    'RightContraction': {'description': 'Right Contraction'},
                    'ScalarProduct': {'description': 'Scalar Product'}
                }
            },
            'NonMetricProducts': {
                'description': 'Non-Metric Products',
                'operations': {
                    'OuterProduct': {'description': 'Outer Product'},
                    'RegressiveProduct': {'description': 'Regressive Product'},
                }
            },
            'SumOperations': {
                'description': 'Sum Operations',
                'operations': {
                    'Addition': {'description': 'Addition'},
                    'Subtraction': {'description': 'Subtraction'}
                }
            }
        }
    },
    'UnaryOperations': {
        'description': 'Unary Operations',
        'arguments': {
            'Grade': {'description': 'Grade'}
        },
        'subgroups': {
            'SignChangeOperations': {
                'description': 'Sign-Change Operations',
                'operations': {
                    'CliffordConjugation': {'description': 'Clifford Conjugation'},
                    'GradeInvolution': {'description': 'Grade Involution'},
                    'Reversion': {'description': 'Reversion'}
                }
            },
            'DualizationOperations': {
                'description': 'Dualization Operations',
                'operations': {
                    'Dualization': {'description': 'Dualization'},
                    'Undualization': {'description': 'Undualization'}
                }
            },
            'NormBasedOperations': {
                'description': 'Norm-Based Operation',
                'operations': {
                    'Inversion': {'description': 'Inversion'},
                    'Normalization': {'description': 'Normalization Under Reverse Norm'},
                    'SquaredReverseNorm': {'description': 'Squared Reverse Norm'},
                }
            },
            'PlusMinusOperations': {
                'description': 'Plus/Minus Operations',
                'operations': {
                    'UnaryMinus': {'description': 'Unary Minus'},
                    'UnaryPlus': {'description': 'Unary Plus'}
                }
            }
        }
    }
}

_OPERATION_KEY_TO_HIERARCHY = {operation_key: (group_key, subgroup_key) for group_key, group_data in OPERATIONS.items() for subgroup_key, subgroup_data in group_data['subgroups'].items() for operation_key in subgroup_data['operations'].keys()}

STATISTICS = {
    'mean': {'description': 'Mean'},
    'median': {'description': 'Median'},
    'stddev': {'description': 'Standard Deviation'}
}

USED_METRIC = 'cpu_time'  # The time that the process actually had the CPU.
# USED_METRIC = 'real_time'  # The wall-clock time, or the actual time taken from the start of the process to the end.


class GABMColormap(colors.Colormap):
    """Colormap for mapping from scalar values from the interval ``[0, 1]`` and GABM message priority values.
    """

    def __init__(self, base_cmap, vmin, vmax, name='from_cmap'):
        colors.Colormap.__init__(self, name=name, N=base_cmap.N)
        self.base_cmap = base_cmap
        self.norm = colors.Normalize(vmin=vmin, vmax=vmax)
        self._message_priority_to_key = {self.norm(message_priority): message_key for message_priority, message_key in _MESSAGE_PRIORITY_TO_KEY.items()}

    def __call__(self, X, alpha=None, bytes=False):
        rgba = self.base_cmap(X, alpha, bytes)
        if not np.iterable(X):
            message_key = self._message_priority_to_key.get(X, None) if X != 0 else None
            if message_key is not None:
                rgba = self.message_key_to_rgba(message_key, alpha)
        else:
            xma = np.ma.array(X, copy=True)
            xa = xma.filled()
            del xma
            it = np.nditer(xa, flags=['multi_index', 'refs_ok'])
            for x in it:
                message_key = self._message_priority_to_key.get(float(x[...]), None) if x[...] != 0 else None
                if message_key is not None:
                    rgba[it.multi_index] = self.message_key_to_rgba(message_key, alpha)
        return rgba

    def _init(self):
        self.base_cmap._init()

    def _resample(self, lutsize):
        self.base_cmap.resample(lutsize)
        
    def message_key_to_rgba(self, message_key, alpha):
        if message_key == 'MISSING_DATA':
            return (1.0, 0.0, 1.0, alpha if alpha is not None else 1.0)
        elif message_key == 'OPERATION_NOT_IMPLEMENTED' or message_key == 'MODEL_NOT_IMPLEMENTED':
            return (1.0, 1.0, 1.0, alpha if alpha is not None else 1.0)
        elif message_key == 'OPERATION_LEADS_TO_COMPILATION_ERROR' or message_key == 'OPERATION_LEADS_TO_RUNTIME_ERROR':
            return (1.0, 0.0, 0.0, alpha if alpha is not None else 1.0)
        else:
            raise NotImplementedError('The message key "%s" is not implemented.' % message_key)

    def reversed(self, name=None):
        self.base_cmap.reversed(name)


def _raw_context_to_partial_context(raw_context: dict) -> dict:
    """Convert the raw context structure into a context structure that includes only the useful field.
    :param raw_context: the context of the benchmark.
    :return: a dictionaty describing the context.
    """
    return {'BuildType': raw_context['library_build_type'], 'NumCPUs': raw_context['num_cpus'], 'MHzPerCPU': raw_context['mhz_per_cpu'], 'CPUScaling': str(raw_context['cpu_scaling_enabled']), 'LoadAvg': str(raw_context['load_avg'][0]) + ''.join(', %s' % str(value) for value in raw_context['load_avg'][1:]), 'Metric': METRICS[USED_METRIC]['description']}


def _context_to_context_key(context: dict) -> Tuple[str, ...]:
    """Convert the context structure into a key for grouping benchmarks evaluated under the same conditions.
    :param context: the context of the benchmark.
    :return: a tuple describing the context.
    """
    return tuple(value for _, value in sorted(context.items()))


def _context_key_to_folder(context_key: Tuple[str, ...]) -> str:
    """Convert the context key into a string.
    :param context_key: the context key of the benchmark.
    :return: a string describing the context.
    """
    return str(context_key[0]) + ''.join(', %s' % str(item) for item in context_key[1:])


def _parse_benchmark_name(name: str) -> Tuple[str, str, str, str, int, dict, dict]:
    """Parse benchmark name to a set of values.
    :param name: the name of the benchmark.
    :return: (solution_key, operation_key, model_key, d, args, extra_context), where 'solution_key' identifies the library, library generator, or code optimizer, 'operation_key' defines the procedure, 'model_key' and 'd' specify an algebra of R^d, 'args' defines the specialization of the procedure to some case, and 'extra_context' defines some useful information about the context.
    """
    params = name.split('/')
    _, _, operation_key = params[0].split('_')
    solution_key, model_key, d, args, extra_context = None, None, None, dict(), dict()
    for pair in params[1:]:
        key, value = pair.split(':')
        if key == 'SystemName' or key == 'SystemVersion' or key == 'CompilerVersion':
            extra_context[key] = value
        elif key == 'CompilerID':
            extra_context['CompilerName'] = _COMPILER_ID_TO_NAME[value]
        elif key == 'Solution':
            solution_key = value
        elif key == 'Model':
            model_key = _MODEL_ID_TO_KEY[int(value, base=16)]
        elif key == 'D':
            d = int(value)
        else:
            try: args[key] = int(value)
            except ValueError: args[key] = value
    return solution_key, operation_key, model_key, d, args, extra_context


def _tabulate_operations_times(data: dict, contexts_keys: set = None, models_keys: set = None, ds: set = None, groups_keys: set = None, subgroups_keys: set = None, operations_keys: set = None, solutions_keys: set = None) -> Tuple[dict, dict, dict]:
    """Returns a dictionary tree whose leaves are instances of numpy.ndarray tabulating the performance times according to the given restrictions.
    :param data: a dictionary tree with data produced by ga-benchmark.
    :param contexts_keys: a set defining the contexts, or None (default) for all contexts.
    :param models_keys: a set defining the models of geometry, or None (default) for all models.
    :param ds: a set defining the dimensionalities of the models of geometry, or None (default) for all dimensionalities.
    :param groups_keys: a set defining the groups of operations, or None (default) for all groups.
    :param subgroups_keys: a set defining the subgroups of operations, or None (default) for all subgroups.
    :param operations_keys: a set defining the operations, or None (default) for all operations.
    :param solutions_keys: a set defining the solutions, or None (default) for all solutions.
    :return: (tables, missing_tables, max_times), where table and missing_tables are dictionary tree oriented, respectively, by context/model/d/solution/group/subgroup/operation/statistics and context/model/d/group/subgroup/operation, whose leaves are instances of numpy.ndarray tabulating, respectively, the performance data and missing data values, according to the given restrictions, and max_times is a dictionary tree oriented by context/model/d whose leaves are floats defining the maximum time value (mean + standard deviation) found.
    """
    domains = dict()
    max_times = dict()
    for context_key in contexts_keys.intersection(data.keys()) if contexts_keys is not None else data.keys():
        _, models = data[context_key]
        for model_key in models_keys.intersection(models.keys()) if models_keys is not None else models.keys():
            dimensions = models[model_key]
            for d in ds.intersection(dimensions.keys()) if ds is not None else dimensions.keys():
                groups = dimensions[d]
                for group_key in groups_keys.intersection(groups.keys()) if groups_keys is not None else groups.keys():
                    subgroups = groups[group_key]
                    for subgroup_key in subgroups_keys.intersection(subgroups.keys()) if subgroups_keys is not None else subgroups.keys():
                        operations = subgroups[subgroup_key]
                        for operation_key in operations_keys.intersection(operations.keys()) if operations_keys is not None else operations.keys():
                            solutions = operations[operation_key]
                            for solution_key in solutions_keys.intersection(solutions.keys()) if solutions_keys is not None else solutions.keys():
                                cases = solutions[solution_key]
                                for case_key, statistics in cases.items():
                                    domains.setdefault(context_key, dict()).setdefault(model_key, dict()).setdefault(d, dict()).setdefault(group_key, dict()).setdefault(subgroup_key, dict()).setdefault(operation_key, set()).add(case_key)
                                    max_times.setdefault(context_key, dict()).setdefault(model_key, dict()).setdefault(d, sys.float_info.min)
                                    max_times[context_key][model_key][d] = max(max_times[context_key][model_key][d], statistics['mean'] + statistics['stddev'])
    tables = dict()
    missing_tables = dict()
    for context_key in contexts_keys.intersection(data.keys()) if contexts_keys is not None else data.keys():
        _, models = data[context_key]
        for model_key in models_keys.intersection(models.keys()) if models_keys is not None else models.keys():
            dimensions = models[model_key]
            for d in ds.intersection(dimensions.keys()) if ds is not None else dimensions.keys():
                groups = dimensions[d]
                for group_key in groups_keys.intersection(groups.keys()) if groups_keys is not None else groups.keys():
                    subgroups = groups[group_key]
                    for subgroup_key in subgroups_keys.intersection(subgroups.keys()) if subgroups_keys is not None else subgroups.keys():
                        operations = subgroups[subgroup_key]
                        for operation_key in operations_keys.intersection(operations.keys()) if operations_keys is not None else operations.keys():
                            shape = tuple(0 for _ in range(len(OPERATIONS[group_key]['arguments'])))
                            for case_keys in domains[context_key][model_key][d][group_key][subgroup_key][operation_key]:
                                shape = tuple(max(dim_size, case_key + 1) for dim_size, case_key in zip(shape, case_keys))
                            missing_tables.setdefault(context_key, dict()).setdefault(model_key, dict()).setdefault(d, dict()).setdefault(group_key, dict()).setdefault(subgroup_key, dict())[operation_key] = np.full(shape, MESSAGES['MISSING_DATA']['priority'], dtype=np.float_)
                            solutions = operations[operation_key]
                            for solution_key in solutions_keys.intersection(solutions.keys()) if solutions_keys is not None else solutions.keys():
                                cases = solutions[solution_key]
                                for case_key, statistics in cases.items():
                                    for statistics_key, time in statistics.items():
                                        tables.setdefault(context_key, dict()).setdefault(model_key, dict()).setdefault(d, dict()).setdefault(solution_key, dict()).setdefault(group_key, dict()).setdefault(subgroup_key, dict()).setdefault(operation_key, dict()).setdefault(statistics_key, np.full(shape, MESSAGES['MISSING_DATA']['priority'], dtype=np.float_))[case_key] = time
    return tables, missing_tables, max_times


def available_data(data: dict) -> Tuple[dict, dict, dict]:
    """Extracts the key values of solutions, models of geometry and operations available in the given tabulated data.
    :param data: a dictionary tree with data produced by ga-benchmark.
    :return: (available_solutions, available_models, available_operations), where available_solutions, available_models, and available_operations are collections including, respectively, all solutions, models of geometry, and operations available in the given data.
    """
    available_solutions = dict()
    available_models = dict()
    available_operations = dict()
    for context_key, (_, models) in data.items():
        for model_key, dimensions in models.items():
            for d, groups in dimensions.items():
                available_models.setdefault(context_key, dict()).setdefault(model_key, set()).add(d)
                for group_key, subgroups in groups.items():
                    for subgroup_key, operations in subgroups.items():
                        for operation_key, solutions in operations.items():
                            available_operations.setdefault(context_key, dict()).setdefault(group_key, dict()).setdefault(subgroup_key, set()).add(operation_key)
                            for solution_key in solutions.keys():
                                available_solutions.setdefault(context_key, set()).add(solution_key)
    return available_solutions, available_models, available_operations


def context_to_str(context: dict) -> str:
    """Convert the context structure into a string.
    :param context: the context of the benchmark.
    :return: a string describing the context.
    """
    return 'Build using %(CompilerName)s (version %(CompilerVersion)s) in "%(BuildType)s" mode; Run on %(SystemName)s (version %(SystemVersion)s), using %(NumCPUs)d X %(MHzPerCPU)d MHz CPU(s); CPU Scaling: %(CPUScaling)s; Load Average: %(LoadAvg)s; Metric: %(Metric)s' % context


def deduce_message_key(data: dict, contexts_keys: set = None, models_keys: set = None, ds: set = None, groups_keys: set = None, subgroups_keys: set = None, operations_keys: set = None, solutions_keys: set = None) -> str:
    """Returns the message key that explains the data betterx according to the given restrictions.
    :param data: a dictionary tree with data produced by ga-benchmark.
    :param contexts_keys: a set defining the contexts, or None (default) for all contexts.
    :param models_keys: a set defining the models of geometry, or None (default) for all models.
    :param ds: a set defining the dimensionalities of the models of geometry, or None (default) for all dimensionalities.
    :param groups_keys: a set defining the groups of operations, or None (default) for all groups.
    :param subgroups_keys: a set defining the subgroups of operations, or None (default) for all subgroups.
    :param operations_keys: a set defining the operations, or None (default) for all operations.
    :param solutions_keys: a set defining the solutions, or None (default) for all solutions.
    :return: the str object defining the message key.
    """
    message_key = 'MISSING_DATA'
    message_priority = MESSAGES[message_key]['priority']
    for context_key in contexts_keys.intersection(data.keys()) if contexts_keys is not None else data.keys():
        _, models = data[context_key]
        for model_key in models_keys.intersection(models.keys()) if models_keys is not None else models.keys():
            dimensions = models[model_key]
            for d in ds.intersection(dimensions.keys()) if ds is not None else dimensions.keys():
                groups = dimensions[d]
                for group_key in groups_keys.intersection(groups.keys()) if groups_keys is not None else groups.keys():
                    subgroups = groups[group_key]
                    for subgroup_key in subgroups_keys.intersection(subgroups.keys()) if subgroups_keys is not None else subgroups.keys():
                        operations = subgroups[subgroup_key]
                        for operation_key in operations_keys.intersection(operations.keys()) if operations_keys is not None else operations.keys():
                            solutions = operations[operation_key]
                            for solution_key in solutions_keys.intersection(solutions.keys()) if solutions_keys is not None else solutions.keys():
                                cases = solutions[solution_key]
                                for statistics in cases.values():
                                    priority = min(statistics['mean'], 0)
                                    if priority < message_priority:
                                        message_key = _MESSAGE_PRIORITY_TO_KEY[priority]
                                        message_priority = priority
    return message_key


def make_performance_charts(data: dict, solutions: dict, folder: str, start_folder: str = os.curdir) -> list:
    """Returns HTML codes describing tables presenting performance charts of the compared solution.
    :param data: a dictionary tree with data produced by ga-benchmark.
    :param solutions: a dictionary to give fancy names to the compared solutions.
    :param folder: the path to the folder where the chart files will be written.
    :parm start_folder: the path to the folder where the HTML code will be placed.
    :return: a list of HTML documents, one for each table.
    """
    MEAN_TIME_AXIS_LABEL = 'Mean Time (ms)'
    TIME_TICKS_COUNT = 6 # Including 0 and max_time
    TOP_COUNT = 3
    plt.ioff()
    itr_count = sum([len(solutions_) if group_key != 'Algorithms' else 1 for _, models in data.values() for dimensions in models.values() for groups in dimensions.values() for group_key, subgroups in groups.items() for operations in subgroups.values() for solutions_ in operations.values()])
    htmls = list()
    with tqdm(desc='Drawing performance charts', total=itr_count) as pbar:
        for context_key, (context, models) in sorted(data.items()):
            context_str = context_to_str(context)
            for model_key, dimensions in sorted(models.items()):
                for d, groups in sorted(dimensions.items()):
                    for group_key in sorted(groups.keys()):
                        axes_labels = [argument_data['description'] for _, argument_data in sorted(OPERATIONS[group_key]['arguments'].items())]
                        tables, missing_tables, max_times = _tabulate_operations_times(data, contexts_keys={context_key}, models_keys={model_key}, ds={d}, groups_keys={group_key})
                        solutions_tables = tables[context_key][model_key][d]
                        missing_subgroups_tables = missing_tables[context_key][model_key][d][group_key]
                        solutions_keys = sorted(list(solutions_tables.keys()))
                        subgroups_keys = sorted(list({subgroup_key for solution_tables in solutions_tables.values() for subgroup_key in solution_tables[group_key].keys()}))
                        operations_keys = sorted(list({(subgroup_key, operation_key) for solution_tables in solutions_tables.values() for subgroup_key, subgroup_tables in solution_tables[group_key].items() for operation_key in subgroup_tables.keys()}))
                        # Set and draw custom color map
                        max_time = max_times[context_key][model_key][d]
                        time_ticks = np.arange(0, TIME_TICKS_COUNT, 1) * (max_time / (TIME_TICKS_COUNT - 1))
                        time_tick_labels = ['%1.4f' % tick for tick in time_ticks]
                        relative_path = os.path.join(_context_key_to_folder(context_key), model_key, str(d), group_key)
                        cmap_filename = os.path.join(folder, relative_path, 'cmap.svg')
                        os.makedirs(os.path.join(folder, relative_path), exist_ok=True)
                        cmap = GABMColormap(plt.get_cmap('coolwarm'), vmin=0, vmax=max_time)
                        cmap_intensity_table = np.arange(cmap.N) / cmap.N
                        fig = plt.figure()
                        plt.subplot2grid((1, 5 + len(MESSAGES)), (0, 0), rowspan=1, colspan=6)
                        plt.imshow(cmap([cmap_intensity_table]), extent=[0, cmap.N, 0, cmap.N / 10])
                        plt.xlabel(MEAN_TIME_AXIS_LABEL)
                        plt.xticks(np.arange(0, cmap.N + 1, cmap.N / (TIME_TICKS_COUNT - 1)), time_tick_labels, rotation=90)
                        plt.yticks([])
                        ind = 1
                        for message_key, message_data in sorted(MESSAGES.items(), reverse=True, key=lambda item: item[1]['priority']):
                            if message_key != 'IMPLEMENTED':
                                plt.subplot2grid((1, 5 + len(MESSAGES)), (0, 5 + ind), rowspan=1, colspan=1)
                                plt.imshow(np.full((1, 1, 3), tuple(int(255 * value) for value in cmap(cmap.norm(message_data['priority']))[:3])), extent=[0, cmap.N / 10, 0, cmap.N / 10], aspect='equal')
                                plt.xlabel(MESSAGES[message_key]['short_description'], rotation=90)
                                plt.xticks([])
                                plt.yticks([])
                                ind += 1
                        fig.tight_layout()
                        if os.path.isfile(cmap_filename):
                            os.remove(cmap_filename)
                        fig.savefig(cmap_filename, bbox_inches='tight')
                        plt.close(fig)
                        # Write HTML code for current group of operations
                        html = '<!DOCTYPE html><html><head><style>table, th, td {border: 1px solid black; border-collapse: collapse; line-height: 1.0} th, td {padding: 5px; text-align: center;}</style></head><body>'
                        html += '<h3>%s %d-D</h3>' % (MODELS[model_key]['description'], d)
                        html += '<h4>%s</h4>' % OPERATIONS[group_key]['description']
                        html += '<p style="line-height: 1.5"><b>Context:</b> %s</p>' % context_str
                        html += '<table style="table-layout: fixed; width: %dpx;">' % (150 * (len(operations_keys) + 1))
                        if group_key == 'Algorithms':
                            top_solutions_keys_per_operation = dict()
                            # Full
                            html += '<tr>'
                            for subgroup_key in subgroups_keys:
                                html += '<th colspan="%d">%s</th>' % (len([operation_key for curr_subgroup_key, operation_key in operations_keys if curr_subgroup_key == subgroup_key]), OPERATIONS[group_key]['subgroups'][subgroup_key]['description'])
                            html += '</tr><tr>'
                            for subgroup_key, operation_key in operations_keys:
                                html += '<th>%s</th>' % OPERATIONS[group_key]['subgroups'][subgroup_key]['operations'][operation_key]['description']
                            html += '</tr><tr>'
                            for _ in operations_keys:
                                html += '<td>All Solutions</td>'
                            html += '</tr><tr>'
                            for subgroup_key, operation_key in operations_keys:
                                relative_path = os.path.join(_context_key_to_folder(context_key), model_key, str(d), group_key, subgroup_key)
                                chart_filename = os.path.join(folder, relative_path, '%s.svg' % operation_key)
                                os.makedirs(os.path.join(folder, relative_path), exist_ok=True)
                                subgroup_table = {statistics_key: [MESSAGES['MISSING_DATA']['priority']] * len(solutions_keys) for statistics_key in STATISTICS.keys()}
                                for solution_ind, solution_key in enumerate(solutions_keys):
                                    for statistics_key in STATISTICS.keys():
                                        subgroup_table[statistics_key][solution_ind] = solutions_tables[solution_key].get(group_key, dict()).get(subgroup_key, dict()).get(operation_key, dict()).get(statistics_key, missing_subgroups_tables[subgroup_key][operation_key])
                                top_solutions_keys_per_operation[operation_key] = set()
                                for ind, (mean_time, solution_key) in enumerate(sorted(zip([mean_time if 0 <= mean_time and mean_time <= max_time else sys.float_info.max for mean_time in subgroup_table['mean']], solutions_keys))):
                                    if ind < TOP_COUNT and mean_time != sys.float_info.max:
                                        top_solutions_keys_per_operation[operation_key].add(solution_key)
                                # Draw bar plot of performance.
                                fig = plt.figure()
                                barlist = plt.bar(np.arange(len(solutions_keys)), [mean_time if 0 <= mean_time and mean_time <= max_time else max_time for mean_time in subgroup_table['mean']], yerr=[stddev_time if 0 <= stddev_time and stddev_time <= max_time else 0 for stddev_time in subgroup_table['stddev']], edgecolor='k', linewidth=1)
                                for bar, mean_time in zip(barlist, subgroup_table['mean']):
                                    bar.set_facecolor(cmap(cmap.norm(mean_time)))
                                ax = plt.gca()
                                ax.set_xticks(np.arange(len(solutions_keys)))
                                ax.set_xticklabels([solutions[solutions_key]['description'] for solutions_key in solutions_keys], rotation=45)
                                ax.set_ylabel(MEAN_TIME_AXIS_LABEL)
                                ax.set_ylim(0, max_time)
                                ax.set_yticks(time_ticks)
                                ax.set_yticklabels(time_tick_labels)
                                plt.grid(linestyle='--', linewidth=2, axis='y', alpha=0.5)
                                if os.path.isfile(chart_filename):
                                    os.remove(chart_filename)
                                fig.savefig(chart_filename, bbox_inches='tight')
                                plt.close(fig)
                                html += '<td><img src="%s?modified=%f" style="max-height:100%%; max-width:100%%"></td>' % (os.path.relpath(chart_filename, start_folder), datetime.timestamp(datetime.now()))
                                pbar.update(1)
                            html += '</tr>'
                            # Top K
                            html += '<tr>'
                            for _ in operations_keys:
                                html += '<td>Top %d</td>' % TOP_COUNT
                            html += '</tr><tr>'
                            for subgroup_key, operation_key in operations_keys:
                                top_tables, _, top_max_times = _tabulate_operations_times(data, contexts_keys={context_key}, models_keys={model_key}, ds={d}, groups_keys={group_key}, subgroups_keys={subgroup_key}, operations_keys={operation_key}, solutions_keys=top_solutions_keys_per_operation[operation_key])
                                top_solutions_tables = top_tables[context_key][model_key][d]
                                top_solutions_keys = sorted(list(top_solutions_tables.keys()))
                                top_max_time = top_max_times[context_key][model_key][d]
                                top_time_ticks = np.arange(0, TIME_TICKS_COUNT, 1) * (top_max_time / (TIME_TICKS_COUNT - 1))
                                top_time_tick_labels = ['%1.4f' % tick for tick in top_time_ticks]
                                relative_path = os.path.join(_context_key_to_folder(context_key), model_key, str(d), group_key, subgroup_key)
                                chart_filename = os.path.join(folder, relative_path, '%s_top_%d.svg' % (operation_key, TOP_COUNT))
                                os.makedirs(os.path.join(folder, relative_path), exist_ok=True)
                                top_subgroup_table = {statistics_key: [MESSAGES['MISSING_DATA']['priority']] * len(top_solutions_keys) for statistics_key in STATISTICS.keys()}
                                for solution_ind, solution_key in enumerate(top_solutions_keys):
                                    for statistics_key in STATISTICS.keys():
                                        top_subgroup_table[statistics_key][solution_ind] = top_solutions_tables[solution_key].get(group_key, dict()).get(subgroup_key, dict()).get(operation_key, dict()).get(statistics_key, missing_subgroups_tables[subgroup_key][operation_key])
                                # Draw bar plot of performance.
                                fig = plt.figure()
                                barlist = plt.bar(np.arange(len(top_solutions_keys)), [mean_time if 0 <= mean_time and mean_time <= top_max_time else top_max_time for mean_time in top_subgroup_table['mean']], yerr=[stddev_time if 0 <= stddev_time and stddev_time <= top_max_time else 0 for stddev_time in top_subgroup_table['stddev']], edgecolor='k', linewidth=1)
                                for bar, mean_time in zip(barlist, top_subgroup_table['mean']):
                                    bar.set_facecolor(cmap(cmap.norm(mean_time)))
                                ax = plt.gca()
                                ax.set_xticks(np.arange(len(top_solutions_keys)))
                                ax.set_xticklabels([solutions[solutions_key]['description'] for solutions_key in top_solutions_keys], rotation=45)
                                ax.set_ylabel(MEAN_TIME_AXIS_LABEL)
                                ax.set_ylim(0, top_max_time)
                                ax.set_yticks(top_time_ticks)
                                ax.set_yticklabels(top_time_tick_labels)
                                plt.grid(linestyle='--', linewidth=2, axis='y', alpha=0.5)
                                if os.path.isfile(chart_filename):
                                    os.remove(chart_filename)
                                fig.savefig(chart_filename, bbox_inches='tight')
                                plt.close(fig)
                                html += '<td><img src="%s?modified=%f" style="max-height:100%%; max-width:100%%"></td>' % (os.path.relpath(chart_filename, start_folder), datetime.timestamp(datetime.now()))
                                pbar.update(1)
                            html += '</tr>'
                        else:
                            html += '<tr><th rowspan="2">Solutions</th>'
                            for subgroup_key in subgroups_keys:
                                html += '<th colspan="%d">%s</th>' % (len([operation_key for curr_subgroup_key, operation_key in operations_keys if curr_subgroup_key == subgroup_key]), OPERATIONS[group_key]['subgroups'][subgroup_key]['description'])
                            html += '</tr><tr>'
                            for subgroup_key, operation_key in operations_keys:
                                html += '<th>%s</th>' % OPERATIONS[group_key]['subgroups'][subgroup_key]['operations'][operation_key]['description']
                            html += '</tr><tr>'
                            for solution_key in solutions_keys:
                                html += '<tr><th white-space: nowrap>%s</th>' % solutions[solution_key]['description']
                                for subgroup_key, operation_key in operations_keys:
                                    relative_path = os.path.join(_context_key_to_folder(context_key), model_key, str(d), group_key, subgroup_key, operation_key)
                                    chart_filename = os.path.join(folder, relative_path, '%s.svg' % solution_key)
                                    os.makedirs(os.path.join(folder, relative_path), exist_ok=True)
                                    operation_table = solutions_tables[solution_key].get(group_key, dict()).get(subgroup_key, dict()).get(operation_key, missing_subgroups_tables[subgroup_key][operation_key])
                                    mean_time_table = operation_table['mean']
                                    stddev_time_table = operation_table['stddev']
                                    fig = plt.figure()
                                    if mean_time_table.ndim == 1:
                                        # Draw bar plot of performance.
                                        barlist = plt.bar(np.arange(mean_time_table.shape[0]), [mean_time if 0 <= mean_time and mean_time <= max_time else max_time for mean_time in mean_time_table], yerr=[stddev_time if 0 <= stddev_time and stddev_time <= max_time else 0 for stddev_time in stddev_time_table], edgecolor='k', linewidth=1)
                                        for bar, mean_time in zip(barlist, mean_time_table):
                                            bar.set_facecolor(cmap(cmap.norm(mean_time)))
                                        ax = plt.gca()
                                        ax.set_xlabel(axes_labels[0])
                                        ax.set_xticks(np.arange(0, mean_time_table.shape[0], 1))
                                        ax.set_ylabel(MEAN_TIME_AXIS_LABEL)
                                        ax.set_ylim(0, max_time)
                                        ax.set_yticks(time_ticks)
                                        ax.set_yticklabels(time_tick_labels)
                                        plt.grid(linestyle='--', linewidth=2, axis='y', alpha=0.5)
                                    elif mean_time_table.ndim == 2:
                                        # Draw heat map of performance.
                                        plt.imshow((255 * cmap(cmap.norm(mean_time_table))).astype(int), interpolation='nearest')
                                        ax = plt.gca()
                                        ax.set_xlabel(axes_labels[1])
                                        ax.set_xticks(np.arange(0, mean_time_table.shape[1], 1))
                                        ax.set_xticklabels(np.arange(0, mean_time_table.shape[1], 1))
                                        ax.set_xticks(np.arange(-0.5, mean_time_table.shape[1], 1), minor=True)
                                        ax.set_ylabel(axes_labels[0])
                                        ax.set_yticks(np.arange(0, mean_time_table.shape[0], 1))
                                        ax.set_yticklabels(np.arange(0, mean_time_table.shape[0], 1))
                                        ax.set_yticks(np.arange(-0.5, mean_time_table.shape[0], 1), minor=True)
                                        ax.grid(which='minor', color='w', linestyle='-', linewidth=2)
                                        fig.tight_layout()
                                    if os.path.isfile(chart_filename):
                                        os.remove(chart_filename)
                                    fig.savefig(chart_filename, bbox_inches='tight')
                                    plt.close(fig)
                                    html += '<td><img src="%s?modified=%f" style="max-height:100%%; max-width:100%%"></td>' % (os.path.relpath(chart_filename, start_folder), datetime.timestamp(datetime.now()))
                                    pbar.update(1)
                                html += '</tr>'
                        html += '</table>'
                        html += '<b>Legend:</b><br>'
                        html += '<img src="%s?modified=%f" style="width: 400px; height: auto">' % (os.path.relpath(cmap_filename, start_folder), datetime.timestamp(datetime.now()))
                        html += '</body></html>'
                        htmls.append(html)
    return htmls
    
    
def make_ranking(data: dict, solutions: dict) -> str:
    """Returns the HTML code describing the ranking of the compared solution.
    :param data: a dictionary tree with data produced by ga-benchmark.
    :param solutions: a dictionary to give fancy names to the compared solutions.
    :return: the HTML document for the ranking.
    """
    def cmp_score_data(lhs, rhs):
        lhs_medals = lhs[1]['medals']
        rhs_medals = rhs[1]['medals']
        if lhs_medals > rhs_medals: return -1
        elif lhs_medals < rhs_medals: return +1
        lhs_faults = lhs[1]['faults']
        rhs_faults = rhs[1]['faults']
        if lhs_faults < rhs_faults: return -1
        elif lhs_faults > rhs_faults: return +1
        lhs_solution_key = lhs[0]
        rhs_solution_key = rhs[0]
        if lhs_solution_key < rhs_solution_key: return -1
        elif lhs_solution_key > rhs_solution_key: return +1
        return 0
    IGNORED_GROUPS = {'Algorithms'}
    NOT_IMPLEMENTED_SET = {MESSAGES[message_key]['priority'] for message_key in {'OPERATION_NOT_IMPLEMENTED', 'MODEL_NOT_IMPLEMENTED'}}
    NOT_IMPLEMENTED_LIST = sorted(NOT_IMPLEMENTED_SET)
    PENALIZED_SET = {MESSAGES[message_key]['priority'] for message_key in {'MISSING_DATA', 'OPERATION_LEADS_TO_COMPILATION_ERROR', 'OPERATION_LEADS_TO_RUNTIME_ERROR'}}
    PENALIZED_LIST = sorted(PENALIZED_SET)
    htmls = list()
    for context_key, (context, models) in sorted(data.items()):
        context_str = context_to_str(context)
        given_solutions_keys = sorted({solution_key for model_key, dimensions in models.items() for d, groups in dimensions.items() for group_key, subgroups in groups.items() for subgroup_key, operations in subgroups.items() for operation_key, solutions_ in operations.items() for solution_key in solutions_.keys() if group_key not in IGNORED_GROUPS})
        html = '<!DOCTYPE html><html><head><style>table, th, td {border: 1px solid black; border-collapse: collapse; line-height: 1.0} th, td {padding: 5px; text-align: center;}</style></head><body>'
        for statistics_key in ['mean']:
            score = {solution_key: {'medals': [0] * len(given_solutions_keys), 'faults': [0] * len(PENALIZED_SET)} for solution_key in given_solutions_keys}
            for model_key, dimensions in sorted(models.items()):
                for d, groups in sorted(dimensions.items()):
                    for group_key in sorted(groups.keys()):
                        if group_key not in IGNORED_GROUPS:
                            tables, missing_tables, _ = _tabulate_operations_times(data, contexts_keys={context_key}, models_keys={model_key}, ds={d}, groups_keys={group_key})
                            solutions_tables = tables[context_key][model_key][d]
                            missing_subgroups_tables = missing_tables[context_key][model_key][d][group_key]
                            subgroups_keys = sorted(list({subgroup_key for solution_tables in solutions_tables.values() for subgroup_key in solution_tables[group_key].keys()}))
                            operations_keys = sorted(list({(subgroup_key, operation_key) for solution_tables in solutions_tables.values() for subgroup_key, subgroup_tables in solution_tables[group_key].items() for operation_key in subgroup_tables.keys()}))
                            for subgroup_key, operation_key in operations_keys:
                                time_tables = np.asarray([solutions_tables[solution_key].get(group_key, dict()).get(subgroup_key, dict()).get(operation_key, missing_subgroups_tables[subgroup_key][operation_key])[statistics_key] for solution_key in given_solutions_keys])
                                times = time_tables[..., ~np.any(np.isin(time_tables, NOT_IMPLEMENTED_LIST), axis=0)]
                                for case_ind in range(times.shape[1]):
                                    classification = sorted([pair for pair in zip(times[..., case_ind], given_solutions_keys)])
                                    classification.insert(0, classification[0])
                                    position = 0
                                    for (prev_time, _), (time, solution_key) in zip(classification[:-1], classification[1:]):
                                        if time not in PENALIZED_SET:
                                            if prev_time != time: position += 1
                                            score[solution_key]['medals'][position] += 1
                                        else:
                                            score[solution_key]['faults'][PENALIZED_LIST.index(time)] += 1
            # Write HTML code for current statistics
            html += '<h3>Medal Table (using %s Time)</h3>' % STATISTICS[statistics_key]['description']
            html += '<p style="line-height: 1.5"><b>Context:</b> %s</p>' % context_str
            html += '<table><tr><th rowspan="2">Solutions</th><th colspan="%d">Medals</th><th colspan="%d">Faults</th></tr><tr>' % (len(given_solutions_keys), len(PENALIZED_LIST))
            for position in range(len(given_solutions_keys)):
                html += '<th>%d</th>' % (position + 1)
            for priopity in PENALIZED_LIST:
                html += '<th>%s</th>' % MESSAGES[_MESSAGE_PRIORITY_TO_KEY[priopity]]['short_description']
            html += '</tr>'
            for solution_key, score_data in sorted(score.items(), key=functools.cmp_to_key(cmp_score_data)):
                html += '<tr><th white-space: nowrap>%s</th>' % solutions[solution_key]['description']
                for count in score_data['medals']:
                    html += '<td>%d</td>' % count
                for count in score_data['faults']:
                    html += '<td>%d</td>' % count
                html += '</tr>'
            html += '</table>'
        html += '</body></html>'
        htmls.append(html)
    return htmls


def make_table_of_features(data: dict, solutions: dict) -> str:
    """Returns the HTML code describing a table summarizing the models of geometry and the operations supported by the compared solution.
    :param data: a dictionary tree with data produced by ga-benchmark.
    :param solutions: a dictionary to give fancy names to the compared solutions.
    :return: the HTML document for the table.
    """
    IGNORED_GROUPS = {'Algorithms'}
    MESSAGES_SYMBOLS = {'MISSING_DATA': '<font color="magenta">&quest;</font>', 'IMPLEMENTED': '&#10003', 'OPERATION_NOT_IMPLEMENTED': '&nbsp', 'MODEL_NOT_IMPLEMENTED': '&nbsp', 'OPERATION_LEADS_TO_COMPILATION_ERROR': '<font color="red">&#9888;</font>', 'OPERATION_LEADS_TO_RUNTIME_ERROR': '<font color="red">&#9888;</font>'}
    data_without_ignored_groups = dict()
    for context_key, (context, models) in data.items():
        for model_key, dimensions in models.items():
            for d, groups in dimensions.items():
                for group_key, subgroups in groups.items():
                    if group_key not in IGNORED_GROUPS:
                        data_without_ignored_groups.setdefault(context_key, (context, dict()))[1].setdefault(model_key, dict()).setdefault(d, dict()).setdefault(group_key, subgroups)
    given_solutions, given_models, given_operations = available_data(data_without_ignored_groups)
    html = '<!DOCTYPE html><html><head><style>.verticalTableHeader {text-align: center; line-height: 1.0; white-space: pre-line; transform: rotate(-90deg); height: 150px;} .verticalTableHeader p {margin: 0 -100%; display: inline-block;} .verticalTableHeader p: before{content: ""; width: 0; padding-top: 110%; display: inline-block; vertical-align: middle;} table, th, td {border: 1px solid black; border-collapse: collapse; line-height: 1.0} th, td {padding: 5px; text-align: center;}</style></head><body>'
    for context_key, (context, _) in sorted(data_without_ignored_groups.items()):
        html += '<h3>Front-End</h3>'
        html += '<p style="line-height: 1.5"><b>Context:</b> %s</p>' % context_to_str(context)
        html += '<table>'
        html += '<tr><th rowspan="3">Solutions</th>'
        html += '<th colspan="%d" rowspan="2">Models of Geometry</th>' % len(given_models[context_key])
        for group_key in sorted(given_operations[context_key].keys()):
            operations_count = 0
            for subgroup_key in sorted(given_operations[context_key][group_key].keys()):
                operations_count += len(OPERATIONS[group_key]['subgroups'][subgroup_key]['operations'])
            html += '<th colspan="%d">%s</th>' % (operations_count, OPERATIONS[group_key]['description'])
        html += '</tr><tr>'
        for group_key in sorted(given_operations[context_key].keys()):
            for subgroup_key in sorted(given_operations[context_key][group_key].keys()):
                html += '<th colspan="%d">%s</th>' % (len(OPERATIONS[group_key]['subgroups'][subgroup_key]['operations']), OPERATIONS[group_key]['subgroups'][subgroup_key]['description'])
        html += '</tr><tr>'
        for model_key in sorted(given_models[context_key].keys()):
            html += '<th class="verticalTableHeader">%s</th>' % MODELS[model_key]['description']
        for group_key in sorted(given_operations[context_key].keys()):
            for subgroup_key in sorted(given_operations[context_key][group_key].keys()):
                for operation_key in sorted(given_operations[context_key][group_key][subgroup_key]):
                    html += '<th class="verticalTableHeader">%s</th>' % OPERATIONS[group_key]['subgroups'][subgroup_key]['operations'][operation_key]['description']
        html += '</tr><tr>'
        for solution_key in sorted(given_solutions[context_key]):
            html += '<tr><th white-space: nowrap>%s</th>' % solutions[solution_key]['description']
            for model_key in sorted(given_models[context_key].keys()):
                message_key = deduce_message_key(data_without_ignored_groups, contexts_keys={context_key}, models_keys={model_key}, solutions_keys={solution_key})
                html += '<td>%s</td>' % MESSAGES_SYMBOLS[message_key if message_key in ('MISSING_DATA', 'MODEL_NOT_IMPLEMENTED') else 'IMPLEMENTED']
            for group_key in sorted(given_operations[context_key].keys()):
                for subgroup_key in sorted(given_operations[context_key][group_key].keys()):
                    for operation_key in sorted(given_operations[context_key][group_key][subgroup_key]):
                        html += '<td>%s</td>' % MESSAGES_SYMBOLS[deduce_message_key(data_without_ignored_groups, contexts_keys={context_key}, models_keys={model_key}, groups_keys={group_key}, subgroups_keys={subgroup_key}, operations_keys={operation_key}, solutions_keys={solution_key})]
            html += '</tr>'
        html += '</table>'
        html += '<p style="line-height: 1.5"><b>Legend:</b></p>'
        html += '<table><tr>'
        for message_key, symbol_value in sorted(MESSAGES_SYMBOLS.items(), reverse=True, key=lambda item: MESSAGES[item[0]]['priority']):
            html += '<td text-align: center>%s</td><td text-align: left>%s</td>' % (symbol_value, MESSAGES[message_key]['description'])
        html += '</tr></table>'
    html += '</body></html>'
    return html
    

def read_data(folder: str, verbose: bool = False) -> dict:
    """Read benchmark results from JSON files found in the given folder and returns tabulated data.
    :param folder: the path to the folder containing the JSON files generated by the ga-benchmark tool.
    :param verbose: indicates whether the processing messages should be displayed (default: False).
    :return: a dictionary tree with data available in the JSON files and oriented by context/model/d/group/subgroup/operation/solution/case/statistics.
    """
    def message(msg, *argv):
        if verbose: print(msg % argv, end='')
    data = dict()
    success, fail = 0, 0
    message('Reading JSON files in "%s"\n', folder)
    for filename in sorted(os.listdir(folder)) if verbose else tqdm(sorted(os.listdir(folder)), desc='Reading JSON files'):
        filepath = os.path.join(folder, filename)
        if os.path.isfile(filepath) and filename.startswith('GABenchmark_') and filename.endswith('.json'):
            message('  Parsing "%s"... ', filename)
            with open(filepath) as f:
                try:
                    raw_data = json.load(f)
                except:
                    fail += 1  # Errors while trying to load JSON data are the only accepted ones.
                    message('error\n')
                    continue
            partial_context = _raw_context_to_partial_context(raw_data.get('context'))
            for bm in raw_data.get('benchmarks', list()):
                solution_key, operation_key, model_key, d, args, extra_context = _parse_benchmark_name(bm['name'])
                group_key, subgroup_key = _OPERATION_KEY_TO_HIERARCHY[operation_key]
                case_key = tuple(args[argument_key] for argument_key in sorted(OPERATIONS[group_key]['arguments'].keys()))
                if bm.get('error_occurred', False):
                    error_message = bm['error_message']
                    statistics_key = None
                    time = None
                    for message_key, message_data in MESSAGES.items():
                        if error_message.startswith(message_key):
                            time = message_data['priority']
                            break
                    if time is None:
                        raise NotImplementedError('The error message "%s" is not supported yet.' % error_message)
                else:
                    statistics_key = bm.get('aggregate_name', None)
                    time = bm[USED_METRIC]
                context = dict(partial_context, **extra_context)
                context_key = _context_to_context_key(context)
                _, models = data.setdefault(context_key, (context, dict()))
                dimensions = models.setdefault(model_key, dict())
                groups = dimensions.setdefault(d, dict())
                subgroups = groups.setdefault(group_key, dict())
                operations = subgroups.setdefault(subgroup_key, dict())
                solutions = operations.setdefault(operation_key, dict())
                cases = solutions.setdefault(solution_key, dict())
                statistics = cases.setdefault(case_key, dict())
                if statistics_key is not None:
                    statistics[statistics_key] = time
                else:
                    for statistics_key in STATISTICS.keys():
                        statistics[statistics_key] = time
            success += 1
            message('done\n')
    message('  Success: %d, Fail: %d\n\n', success, fail)
    return data


def main(argsv=None):
    """Main function.
    """
    if argsv is None: argsv = sys.argv[1:]

    ap = argparse.ArgumentParser('python3 -m plot [-i INPUT_FOLDER] [-o OUTPUT_FOLDER] [-s]')
    ap.add_argument('-i', '--input', metavar='INPUT_FOLDER', required=False, default='.', help='Folder containing the JSON files generated by the ga-benchmark tool (default: current folder).')
    ap.add_argument('-o', '--output', metavar='OUTPUT_FOLDER', required=False, default='./results', help='Folder to which the charts and tables will be exported (default: [current folder]/results).')
    ap.add_argument('-s', '--silent', required=False, default=False, action='store_true', help='Defines whether the processing messages should be skipped. (default: False).')

    args = vars(ap.parse_args(argsv))

    SOLUTIONS = {  # You have to include your solution here if you have added it to ga-benchmark.
        'Gaalet': {'description': 'Gaalet'},
        'Gaalop': {'description': 'Gaalop'},
        'Garamon': {'description': 'Garamon'},
        'GATL': {'description': 'GATL'},
        'GluCatFramedMulti': {'description': 'GluCat (framed)'},
        'GluCatMatrixMulti': {'description': 'GluCat (matrix)'},
        'TbGAL': {'description': 'TbGAL'},
        'Versor': {'description': 'Versor'}
    }

    input_folder = args['input']
    output_folder = args['output']

    data = read_data(folder=input_folder, verbose=not args['silent'])

    os.makedirs(os.path.join(output_folder, 'data'), exist_ok=True)
    for filename in os.listdir(input_folder):
        filepath = os.path.join(input_folder, filename)
        if os.path.isfile(filepath) and filename.startswith('GABenchmark_') and filename.endswith('.json'):
            shutil.copy2(filepath, os.path.join(output_folder, 'data'))

    with open(os.path.join(output_folder, 'table_of_features.html'), 'w') as out:
        out.write(make_table_of_features(data=data, solutions=SOLUTIONS))
    
    for ind, html in enumerate(make_ranking(data=data, solutions=SOLUTIONS), 1):
        with open(os.path.join(output_folder, 'ranking_%d.html' % ind), 'w') as out:
            out.write(html)

    for ind, html in enumerate(make_performance_charts(data=data, solutions=SOLUTIONS, folder=output_folder, start_folder=output_folder), 1):
        with open(os.path.join(output_folder, 'performance_charts_%d.html' % ind), 'w') as out:
            out.write(html)


if __name__ == "__main__":
    main()