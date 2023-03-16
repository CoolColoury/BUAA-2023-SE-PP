import os.path
import random
from xml.dom import minidom
from xml.etree import ElementTree as ET


def write_to_file(data, src):
    with open(src, "w") as f:
        f.write(data)


def parse_config_xml():
    configs = []
    tree = ET.parse('config.xml')
    root = tree.getroot()
    for _config in root:
        config = _config.attrib
        for _info in _config:
            config.update({_info.tag: _info.text})
        configs.append(config)
    return configs


def prettify(root):
    """将节点转换成字符串，并添加缩进

    :param root:
    :return:
    """
    rough_string = ET.tostring(root, encoding='utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="\t")



def init_config_xml():
    """ 在根路径下创建config.xml

    :return:
    """
    random.seed(0x19260817)
    root = ET.Element('root')

    for i in range(10):
        config = ET.Element('config', {'id': str(i + 1)})
        seed = ET.Element('seed')
        seed.text = str(random.randint(0, 1000000))
        word_num = ET.Element('word-num')
        word_num.text = str(10000)
        max_word_length = ET.Element('max-word-length')
        max_word_length.text = str(100)
        special = ET.Element('special')
        special.text = str(0)
        config.append(seed)
        config.append(word_num)
        config.append(max_word_length)
        config.append(special)
        root.append(config)

    config_xml = prettify(root)
    write_to_file(config_xml, 'config.xml')


if __name__ == '__main__':
    if not os.path.exists('config.xml'):
        init_config_xml()
