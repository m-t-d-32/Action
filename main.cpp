#include "Action.h"
using namespace Action;

int main()
{
    //现在使用我们的库开始工作！

    //首先输出最简单的Hello World！
    String hello="Hello World!";
    hello.println();

    //现在学会使用整数和实数！
    Integer a=3,b=4;
    (a+b).println();
    (a-b).println();
    (a*b).println();
    (a/b).println();    //这里会输出实数！
    (a DIV b).println();    //这句话能达到原本C++语言里两个整数相除的效果。
    (a MOD b).println();    //还记得%取余符号吗？这里用MOD代替了。

    //现在学会使用数组！
    ArrayList<Integer> my_array;    //直接创建一个动态数组，就像使用vector一样。
    my_array.push_back(100);  //在数组的最后追加元素
    my_array.println(); //输出
    my_array.insert(0,4);   //在第0个位置插入整数4
    my_array.erase(1);  //移除第1个位置的数（100）
    my_array.println();

    //现在创建一个集合，集合里面的元素是不重复的。
    HashSet<String> my_set;
    my_set.insert("Bye");
    my_set.insert("Hello");
    my_set.insert("Bye");
    my_set.println();   //尝试输出它们，这些元素都是无序的。

    //字典是使用哈希结构实现的，使用字典可以提高查找效率。
    HashMap<String,Integer> my_map; //创建字典，键是String，值是Integer
    my_map.insert("China",1);
    my_map["America"]=2;    //这是另一种插入方式
    my_map.insert("China",2);   //如果插入重复的键，那么对应的值会被替换
    my_map.println();

    //队列和栈会给程序设计带来方便，现在尝试使用它们！
    Queue<Integer> my_que;
    my_que.push(3);
    my_que.push(2);
    my_que.front().println();
    my_que.pop();   //移除队头的元素
    my_que.println();   //再看一次，里面只有一个元素了

    Stack<String> my_stk;
    my_stk.push("Hello");
    my_stk.push("Bye");
    my_stk.pop().println(); //先入后出哦

    //堆可以作为优先队列，兼顾时间和空间复杂度。
    //这里不再演示，使用者可以自己试试看！

    //感谢使用！
    //Powered By Windows NT Version 6.0 Pre.
    return 0;
}
