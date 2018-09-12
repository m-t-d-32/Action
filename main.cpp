#include "Action.h"
#include <stdlib.h>
#include <time.h>
using namespace Action;

int main()
{
    //现在使用我们的库开始工作！
    srand(time(NULL));  //做一些随机数的准备

    //首先输出最简单的Hello World！
    String hello = "Hello World!";
    hello.println();
    (hello + " We are coding now!").println();   //正像你想的那样，两个字符串可以拼接。

    //现在学会使用整数和实数！
    Integer a = 3, b = 4;
    (a + b).println();
    (a - b).println();
    (a * b).println();
    (a / b).println();  //这里会输出实数！
    (a DIV b).println();    //这句话能达到原本C++语言里两个整数相除的效果。
    (a MOD b).println();    //还记得%取余符号吗？这里用MOD代替了。

    //现在学会使用数组！
    ArrayList<Integer> my_array;    //直接创建一个动态数组，就像使用vector一样。
    my_array.push_back(100);  //在数组的最后追加元素
    my_array.println(); //输出
    my_array.insert(0, 4);  //在第0个位置插入整数4
    my_array.erase(1);  //移除第1个位置的数（100）
    my_array.println();

    //链表和数组都是线性结构，链表可以最大程度地利用空间。
    LinkedList<Integer> my_links;
    my_links.push_back(1);
    my_links.push_back(3);
    my_links.println();
    for(LinkedList<Integer>::Pointer it = my_links.begin(); it != my_links.end(); ++it)
    {
        (*it).println();    //让我们用迭代器把元素遍历输出吧！
    }
    String("The following operation is deprecated!").println();
    my_links[1].println();  //不到迫不得已的时候不要下标访问，如果真的需要，请使用ArrayList！

    //现在创建一个集合，集合里面的元素是不重复的。
    HashSet<String> my_set;
    my_set.insert("Bye");
    my_set.insert("Hello");
    my_set.insert("Bye");
    my_set.println();   //尝试输出它们，这些元素都是无序的。

    //有序的集合TreeSet可以帮我们排序哦，让我们试一试！
    TreeSet<Integer> another_set;
    for(int i = 0; i < 100; ++i)
    {
        another_set.insert(rand() % 50);
    }
    another_set.println();  //可以看出TreeSet不仅去掉了重复元素，而且排好了序。

    //字典是使用哈希结构实现的，使用字典可以提高查找效率。
    HashMap<String, Integer> my_map; //创建字典，键是String，值是Integer
    my_map.insert("China", 1);
    my_map["America"] = 2;  //这是另一种插入方式
    my_map.insert("China", 2);  //如果插入重复的键，那么对应的值会被替换
    my_map.println();   //现在打印一下结果
    my_map.clear();     //如果要清空整个字典，可以使用clear方法。
    for(int i = 0; i < 100; ++i)    //现在用随机数试试它们是否有序
    {
        String temp;
        for(int j = 0; j < 5; ++j)
        {
            temp += (rand() % 26 + 'a');
        }
        my_map.insert(temp, rand());
    }
    my_map.println();   //可以发现，它们是无序的。

    //带排序的字典内部使用二叉树实现，因此它们有序，让我们再把刚才的实验做一遍。
    TreeMap<String, Integer> another_map;
    for(int i = 0; i < 100; ++i)    //两种字典的方法几乎完全相同。
    {
        String temp;
        for(int j = 0; j < 5; ++j)
        {
            temp += (rand() % 26 + 'a');
        }
        another_map.insert(temp, rand());
    }
    another_map.println();   //可以发现，它们是有序的。

    //队列和栈会给程序设计带来方便，现在尝试使用它们！
    Queue<Integer> my_que;
    my_que.push(3);
    my_que.push(2);
    my_que.front().println();
    my_que.pop();   //移除队头的元素
    my_que.println();   //再看一次，里面只有一个元素了

    Deque<Integer> my_dqe;  //双端队列可以在两端插入或者取出元素
    my_dqe.push_back(5);
    my_dqe.push_back(6);
    my_dqe.push_front(7);
    my_dqe.push_front(8);
    my_dqe.println();
    my_dqe[2].println();    //下标访问某个元素
    my_dqe.pop_back().println();
    my_dqe.pop_front().println();
    my_dqe.println();

    Stack<String> my_stk;
    my_stk.push("Hello");
    my_stk.push("Bye");
    my_stk.pop().println(); //先入后出哦

    //使用堆（Heap）可以实现优先队列的功能，我们可以用Heap类构建一个最小堆。
    ArrayList<Integer> temp_array;
    for(int i = 0; i < 10; ++i)
    {
        temp_array.push_back(rand());
    }
    Heap<Integer> my_heap(temp_array);
    my_heap.println();  //根据打印的数据，你能否画出一个最小堆呢？试试看吧！

    //感谢使用！
    //Powered By Windows NT Version 6.0 Pre.
    return 0;
}
