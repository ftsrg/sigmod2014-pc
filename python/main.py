import argparse
from collections import namedtuple
import re
from queries.Query1 import Query1
#from queries.Query2 import Query2
from queries.Query3 import Query3
from queries.Query4 import Query4

Test = namedtuple('Test', ['inputs', 'expected_result'])


def load_query_params(path):
    query1_benchmark_tests = []
    query2_benchmark_tests = []
    query3_benchmark_tests = []
    query4_benchmark_tests = []
    with open(path) as file:
        line = file.readline()
        cnt = 1
        while line:
            search_query_num = re.search(r"\d", line)
            if search_query_num is not None:
                query_num = search_query_num.group()[0]
                query_result = line.split(')')[1].strip()
                extracted_params_str = line[line.find("(")+1:line.find(")")]
                extracted_params_list = extracted_params_str.split(',')
                if query_num is '1':
                    person1_id = int(extracted_params_list[0])
                    person2_id = int(extracted_params_list[1])
                    freq_comm_th = int(extracted_params_list[2])
                    test_case = Test([person1_id, person2_id, freq_comm_th], query_result)
                    query1_benchmark_tests.append(test_case)
                elif query_num is '2':
                    top_k = int(extracted_params_list[0])
                    birthday_limit = extracted_params_list[1]
                    test_case = Test([top_k, birthday_limit], query_result)
                    query2_benchmark_tests.append(test_case)
                elif query_num == '3':
                    k = int(extracted_params_list[0])
                    h = int(extracted_params_list[1])
                    p = extracted_params_list[2].strip()
                    test_case = Test([k, h , p], query_result)
                    query3_benchmark_tests.append(test_case)
                elif query_num is '4':
                    k = int(extracted_params_list[0])
                    t = extracted_params_list[1].strip()
                    test_case = Test([k , t], query_result)
                    query4_benchmark_tests.append(test_case)
            else:
                raise Exception('Invalid query input format')
            line = file.readline()
            cnt += 1

    return query1_benchmark_tests, query2_benchmark_tests, query3_benchmark_tests, query4_benchmark_tests


if __name__ == '__main__':

    argparse_formatter = lambda prog: argparse.RawDescriptionHelpFormatter(prog, max_help_position=60, width=250)

    parser = argparse.ArgumentParser(formatter_class=argparse_formatter, description='Run tool to benchmark queries')

    parser.add_argument('--data_path', default='../csvs/o1k/', help='[REQUIRED] Data to use (vertices and edges)')
    parser.add_argument('--query_args_path', default='/Users/attilanagy/Work/paper-hpec2020/docs/sf1k/1k.txt', help='Input parameters for the queries')
    parser.add_argument('--queryies_to_run', default='all', choices=['1', '2', '3', '4', 'all'], help='[REQUIRED] Query to run')

    args = parser.parse_args()

    data_dir = args.data_path
    data_format = 'csv'

    q1_params, q2_params, q3_params, q4_params = load_query_params(args.query_args_path)
    print(q1_params)
    q1 = Query1(data_dir, data_format)
    #q2 = Query2(data_dir, data_format)
    q3 = Query3(data_dir, data_format)
    q4 = Query4(data_dir, data_format)

    q1.init_benchmark_inputs(q1_params)
    #q2.init_benchmark_input(q2_params)
    q3.init_benchmark_inputs(q3_params)
    q4.init_benchmark_inputs(q4_params)


    tests_passed = True

    tests_passed = q1.run_tests(q1.execute_query, mode='benchmark') and tests_passed
    #tests_passed = q2.run_tests(q2.execute_query) and tests_passed
    tests_passed = q3.run_tests(q3.execute_query) and tests_passed
    tests_passed = q4.run_tests(q4.execute_query) and tests_passed

    if tests_passed:
        print('\nALL TESTS PASSED')
    else:
        print('\nTESTS FAILED')