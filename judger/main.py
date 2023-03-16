import os
import time
from func_timeout import func_timeout, FunctionTimedOut


def run_in_terminal(test_id, inputfile):
    print('测试 {}'.format(inputfile))
    start_time = time.time()

    os.system("Wordlist.exe -c {} -r > solutions/solution{}.txt".format(inputfile, test_id))

    end_time = time.time()
    print('程序运行时间: %s秒' % (end_time - start_time))
    return end_time - start_time


if __name__ == '__main__':
    result = ""
    for i in range(6, 16):
        try:
            duration = func_timeout(100,  run_in_terminal, args=(i, "data/data{}.txt".format(i)))
            result += "".join([str(i), ':', str(duration), '\n'])
        except FunctionTimedOut as e:
            print(e)
            result += "".join([str(i), ':', "TLE", '\n'])

    with open("result.txt", "w") as f:
        f.write(result)



