import argparse


def get_id_from_alpha(c):
    if 65 <= ord(c) <= 90:  # 如果c是大写字母
        return ord(c) - 65  # 转换成小写字母
    elif 97 <= ord(c) <= 122:  # 如果c是小写字母
        return ord(c) - 97  # 转换成大写字母
    return -1


def check_format(input_list, o_type=None, head=None, tail=None, n_head=None, enable_loop=False):
    if len(input_list) == 0:
        return 0
    if head is not None and input_list[0][0] != head:
        raise ValueError('错误的首字母')
    if tail is not None and input_list[-1][-1] != tail:
        raise ValueError('错误的尾字母')
    pre_tail = input_list[0][0]
    length = 0
    self_loop_count = [0 for _ in range(26)]
    vis = [0 for _ in range(26)]
    for i in input_list:
        if pre_tail != i[0]:
            raise ValueError('首尾不相连')
        if n_head is not None and i[0] != n_head:
            raise ValueError('不允许的首字母')
        pre_tail = i[-1]
        if o_type == 'w':
            length += len(i)
        elif o_type == 'c':
            length += 1
        if i[0] == i[-1]:
            self_loop_count[get_id_from_alpha(i[-1])] += 1
        else:
            vis[get_id_from_alpha(i[-1])] += 1
    if not enable_loop:
        for i in vis:
            if i >= 2:
                raise ValueError('我超，环')
        for i in self_loop_count:
            if i >= 2:
                raise ValueError('我超，两个自环')
    return length

def compare_file(file1, file2):
    input1 = []
    with open(file1, "r") as f1:
        input1 = f1.read().splitlines()
    input2 = []
    with open(file2, "r") as f2:
        input2 = f2.read().splitlines()
    input2 = input2[1:]
    len1 = check_format(input1, 'c')
    len2 = check_format(input2, 'c')
    if len1 != len2:
        raise ValueError('不相等')

parser = argparse.ArgumentParser()
parser.add_argument("-f", "--file")
parser.add_argument("-n", "--number")
parser.add_argument("-w", "--word")
parser.add_argument("-c", "--char")
parser.add_argument("-he", "--head")
parser.add_argument("-t", "--tail")
parser.add_argument("-j", "--n_head")
parser.add_argument("-r", "--enable_loop", action="store_true")

if __name__ == '__main__':
    args = parser.parse_args()
    input_file = args.file
    input_list = []

    o_type = None
    if args.word:
        o_type = 'w'
    elif args.char:
        o_type = 'c'

    head = args.head
    tail = args.tail
    n_head = args.n_head
    enable_loop = args.enable_loop
    with open(input_file) as _input_file:
        for _input_line in _input_file:
            input_list.append(_input_line.strip().lower())
    try:
        print(check_format(input_list, o_type, head, tail, n_head, enable_loop))
    except ValueError as e:
        print(e)
