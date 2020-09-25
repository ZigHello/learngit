1.安装vs；
2.配置环境变量；
3.编译create.cpp文件；
4.执行“create >whitelist 10”生成文件whitelist；
5.执行“create >q 1000”生成文件q；
6.编译brute.cpp文件；
7.执行“brute -w whitelist < q > output”。
8.better.cpp是brute.cpp的优化版本