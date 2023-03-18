import os
import time
from shutil import copyfile

from func_timeout import func_timeout, FunctionTimedOut

from check import compare_file


def run_in_terminal(inputfile, program_id, test_id):
    if os.path.exists(".\\solution.txt"):
        os.remove(".\\solution.txt")
    print('测试 {}'.format(inputfile))
    program_path = ".\\program\\{}\\Wordlist.exe".format(program_id)

    start_time = time.time()
    os.system("{} -w {}".format(program_path, inputfile))
    end_time = time.time()
    print('程序运行时间: %s秒' % (end_time - start_time))

    solution_dir = ".\\solutions\\{}\\{}".format(program_id, test_id)
    if not os.path.exists(solution_dir):
        os.mkdir(solution_dir)
    copyfile(".\\solution.txt", solution_dir + "\\solution.txt")

    return end_time - start_time


if __name__ == '__main__':
    result = ""
    for i in range(16, 17):
        for p in range(0, 2):
            try:
                duration = func_timeout(100, run_in_terminal, args=("data/data{}.txt".format(i), p, i))
                result += "".join([str(i), ':', str(duration), '\n'])
            except FunctionTimedOut as e:
                print(e)
                result += "".join([str(i), ':', "TLE", '\n'])
        compare_file(".\\solutions\\0\\{}\\solution.txt".format(i),
                     ".\\solutions\\1\\{}\\solution.txt".format(i))
    with open("result.txt", "w") as f:
        f.write(result)
