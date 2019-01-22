#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;

ofstream ocout;
int shudo[9][9];
bool set(int x,int y,int val)
{
    if(shudo[x][y]!=0)        //非空
        return false;    
    int x0,y0;
    
    for(y0=0;y0<9;y0++)      //行冲突
	    if(shudo[x][y0]==val)
	        return false;
	        
    for(x0=0;x0<9;x0++)        //列冲突  
        if(shudo[x0][y]==val)
            return false;
            
    for(x0=x/3*3;x0<x/3*3+3;x0++)        //格冲突
        for(y0=y/3*3;y0<y/3*3+3;y0++)
            if(shudo[x0][y0]==val)
                return false;
                
    shudo[x][y]=val;
    return true;
}

void current(int* cur)     ///0~9随机序列
{
    int i,j,temp;
    for(int i=0;i<9;i++)
    {
        cur[i]=i;
    }
    for(int i=0;i<9;i++)
    {
        j=rand()%9;
        temp=cur[j];
        cur[j]=cur[i];
        cur[i]=temp;
    }
}

void reset(int x,int y)
{
    shudo[x][y]=0;
}

bool fill(int x,int val)
{
    int cur[9];
    current(cur);    //生成当前行的扫描序列
    for(int i=0;i<9;i++)
    {
        int y=cur[i];
        if(set(x,y,val))    //可以先把每一行的1填了，再填每一行的2...以此类推
        {
            if(x==8)    //到了最后一行
            {
                if(val==9||fill(0,val+1))    //当前填9则结束，否则从第一行填下一个数
                    return true;
            }
            else
            {
                if(fill(x+1,val))    //下一行继续填当前数
                    return true;    
            }
            reset(x,y);        //回溯
        }
    }
    return false;
}
void clear(int temp[9][9])    //清空
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            temp[i][j]=0;
        }
    }
}

void printshudo()        //输出到屏幕
{
    for(int x=0;x<9;x++)
    {
        (x%3==0)?(cout<<"  -----------------------\n "):(cout<<" ");
        cout<<"| ";
        for(int y=0;y<9;y++)
        {
            cout<<shudo[x][y]<<" ";
            (y%3==2)?(cout<<"| "):(cout<<"");
        }
        cout<<endl;
    }
    cout<<"  -----------------------\n"<<endl;
}

void printshudotxt()        //输出到sudotiku.txt
{
    for(int x=0;x<9;x++)
    {
        (x%3==0)?(ocout<<"  -----------------------\n "):(ocout<<" ");
        ocout<<"| ";
        for(int y=0;y<9;y++)
        {
            ocout<<shudo[x][y]<<" ";
            (y%3==2)?(ocout<<"| "):(ocout<<"");
        }
        ocout<<endl;
    }
    ocout<<"  -----------------------\n"<<endl;
}


int main()
{
    srand((unsigned)time(NULL));    //这个是种子函数 为rand函数提供不同的种子 每次运行程序产生不同的随机数,不然rand函数每次运行程序产生的随机数都是一样的
    ocout.open("sudoku.txt");
    cout<<"请输入数独棋盘题目个数N (0 < N <= 1000000):"<<endl;
    int N;
    cin>>N;
    cout<<"随机生成"<<N<<"个不重复的已解答完毕的数独棋盘如下:"<<endl;
    ocout << "随机生成"<<N<<"个不重复的已解答完毕的数独棋盘如下:" << endl;
    for(int i=0;i<N;i++)
    {
        clear(shudo);
        while(!fill(0,1));
        printshudo();
        printshudotxt();
    }
    ocout.close();
    return 0;
}