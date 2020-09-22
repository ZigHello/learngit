#-*- codeing = utf-8 -*-
#@Time : 2020/9/21 14:35
#@Author ：张宵
#@File : wf.py
#@Software: PyCharm
import os
import re
import getopt
import sys

def words_split(text):
    strl_list = text.replace('\n', ' ').replace('.', ' ').replace(',', ' ').\
                replace('!', ' ').replace('\\', ' ').replace('#', ' ').\
                replace('[', ' ').replace(']', ' ').replace(':', ' ').\
                replace('?', ' ').replace('-', ' ').replace('\'', ' ').\
                replace('\"', ' ').replace('(', ' ').replace(')', ' ').\
                replace('—', ' ').replace(';', ' ').lower().split()
    count_dict = {}
    # 如果字典里有该单词则加1，否则添加入字典
    for str in strl_list:
        if str in count_dict.keys():
            count_dict[str] = count_dict[str] + 1
        else:
            count_dict[str] = 1
    # 按照词频从高到低排列
    count_list = sorted(count_dict.items(), key=lambda x: x[1], reverse=True)
    return count_list

def read_text(text):
    # 文章字符串前期处理
    #文件读取 open(filename,mode,buffering,encoding)方法
    f = open(text, 'r', -1, 'utf-8')
    # 读取文本内容并将字母全部转换为小写形式
    after_txt = f.read().lower()
    return words_split(after_txt)

def in_out(argv, flag):

    if len(argv) == 2:     #功能一
        try:
            list = read_text(argv[-1])
            opts, args = getopt.getopt(argv, "sh", ["ifile", "ofile"])  # 设置命令行参数
        except getopt.GetoptError:
            print("test.py -i <inputfile> -o <outputfile>")
            sys.exit(2)
        for opt, arg in opts:
            if opt == "-s":  # 命令行参数为-s时执行的操作
                num = len(list)
                print('total', num)
                print('\n')
                for word in list:
                    print('{:20s}{:>5d}{}'.format(word[0], word[1], '\n'))
            elif opt == "-h":
                print("please input the parameter")

    elif len(argv) == 1:
        pattern = re.compile('.+\.txt')
        folder_name = argv[-1]
        m = re.findall(pattern, folder_name)
        if len(m) != 0:  # 功能二，参数以.txt结尾的文件名，直接执行词频操作
            arry = read_text(argv[-1])
            if flag == 0:  # 标志位为0，把所有单词都列出来
                print('total', len(arry), 'words')
                print('\n')
                for item in arry:
                    print('{:20s}{:>5d}{}'.format(item[0], item[1], '\n'))
            else:  # 标志位不为0，只列出前十
                print('total', len(arry), 'words')
                print('\n')
                if len(arry) > 10:
                    for i in range(10):
                        print('{:20s}{:>5d}'.format(arry[i][0], arry[i][1]))
                else:  # 如果本身不超过10个单词量，则列出所有单词即可
                    for item in arry:
                        print('{:20s}{:>5d}'.format(item[0], item[1]))
        else:            #功能三，有多个文件，打开文件夹
            os.chdir(folder_name)  # 文件夹操作
            filename_list = os.listdir()
            for file_name in filename_list:
                print(file_name[:-4] + '\n')
                file_list = [file_name]
                in_out(file_list, 1)  # 得到文件名，进行递归操作，标志位置1，说明要取前10
                print('----\n')

    elif len(argv) == 0:  # 命令行参数为0
        text_contents = input()  # 获取输入数据
        count_list = words_split(text_contents)  # 调用分词逻辑方法
        print('total', len(count_list))  # 打印结果
        for word in count_list:
            print('{:20s}{:>5d}{}'.format(word[0], word[1], '\n'))


def main(argv):

    if( len(sys.argv) == 1 ):
        in_out(argv, 0)
    elif sys.argv[1] == "-s":
        if( len(sys.argv) == 3 ):
           in_out(argv, 0)
        else:
             #重定向获取文件名
             redirect_words = input().lower()  # 获取重定向文本信息并把单词转换为小写
             count_list = words_split(redirect_words)  # 调用分词逻辑方法
             print('total', len(count_list))  # 打印结果
             for word in count_list:
                 print('{:20s}{:>5d}{}'.format(word[0], word[1], '\n'))
    else:
        in_out(argv, 0)

if __name__ == "__main__":
    main(sys.argv[1:])


