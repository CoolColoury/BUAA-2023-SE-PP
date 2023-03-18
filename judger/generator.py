import random

from xml_utils import parse_config_xml, write_to_file

num_node = 26  # 设置图中节点数量
def get_no_loop_edges(edge_num):  # 生成DAG，存入以c命名的文件内
    node = list(range(num_node))  # 将格式转换成list，便于下一步随机重排
    random.shuffle(node)  # 随机重排
    edges = []
    for i in range(edge_num):
        p1 = random.randint(0, num_node - 2)  # 选择第一个节点
        p2 = random.randint(p1 + 1, num_node - 1)  # 选择第二个节点，这个节点的拓扑序必须大于第一个节点
        edges.append((node[p1], node[p2]))
    return edges


def get_random_edges(edge_num):
    edges = []
    for i in range(edge_num):
        p1 = random.randint(0, num_node - 1)  # 选择第一个节点
        p2 = random.randint(0, num_node - 1)  # 选择第二个节点
        edges.append((p1, p2))
    return edges

# 定义一个函数，判断一个字符是否是大小写字母
def is_letter(c):
    return c >= 'A' and c <= 'Z' or c >= 'a' and c <= 'z'


# 定义一个空列表，用于存储除大小写字母外的ascii符号
symbols = []


def get_splitter():
    def init_symbols():
        # 遍历ascii码表中的第32~126个字符（0x20~0x7E）
        for i in range(32, 127):
            # 将整数转换为对应的字符
            c = chr(i)
            # 如果不是大小写字母，就添加到符号列表中
            if not is_letter(c):
                symbols.append(c)
        symbols.append('\n')

    if len(symbols) == 0:
        init_symbols()
    splitter = ""
    length = random.randint(1, 10)
    for _ in range(length):
        splitter += random.choice(symbols)
    return splitter


def shuffle_upper_or_lower(alpha):
    if random.randint(0, 1) == 1:
        return chr(alpha + 97)
    else:
        return chr(alpha + 65)


def get_one_word(config, head, tail):
    word = shuffle_upper_or_lower(head)
    length = random.randint(int(config['max-word-length']) * 2 // 3, int(config['max-word-length']))

    for _ in range(length - 2):
        word += shuffle_upper_or_lower(random.randint(0, 25))

    word += shuffle_upper_or_lower(tail)
    return word


def get_one_test_point(config):
    random.seed(int(config['seed']))
    result = ''

    if config['special'] == 'nr':
        edges = get_no_loop_edges(int(config['word-num']))
        for edge in edges:
            result += get_one_word(config, edge[0], edge[1]) + '\n'
        # 添加自环
        for i in range(26):
            result += get_one_word(config, i, i) + '\n'
    elif config['special'] == 'r':
        edges = get_random_edges(int(config['word-num']))
        for edge in edges:
            result += get_one_word(config, edge[0], edge[1]) + get_splitter()
    else:
        raise ValueError('Unknown Special {}'.format(config['special']))

    return result


if __name__ == '__main__':

    configs = parse_config_xml()
    for config in configs:
        data = get_one_test_point(config)
        # print(data)
        write_to_file(data, 'data/data{}.txt'.format(config['id']))
