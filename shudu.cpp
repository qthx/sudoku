#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;

ofstream ocout;
int shudo[9][9];
bool set(int x,int y,int val)
{
    if(shudo[x][y]!=0)        //�ǿ�
        return false;    
    int x0,y0;
    
    for(y0=0;y0<9;y0++)      //�г�ͻ
	    if(shudo[x][y0]==val)
	        return false;
	        
    for(x0=0;x0<9;x0++)        //�г�ͻ  
        if(shudo[x0][y]==val)
            return false;
            
    for(x0=x/3*3;x0<x/3*3+3;x0++)        //���ͻ
        for(y0=y/3*3;y0<y/3*3+3;y0++)
            if(shudo[x0][y0]==val)
                return false;
                
    shudo[x][y]=val;
    return true;
}

void current(int* cur)     ///0~9�������
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
    current(cur);    //���ɵ�ǰ�е�ɨ������
    for(int i=0;i<9;i++)
    {
        int y=cur[i];
        if(set(x,y,val))    //�����Ȱ�ÿһ�е�1���ˣ�����ÿһ�е�2...�Դ�����
        {
            if(x==8)    //�������һ��
            {
                if(val==9||fill(0,val+1))    //��ǰ��9�����������ӵ�һ������һ����
                    return true;
            }
            else
            {
                if(fill(x+1,val))    //��һ�м����ǰ��
                    return true;    
            }
            reset(x,y);        //����
        }
    }
    return false;
}
void clear(int temp[9][9])    //���
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            temp[i][j]=0;
        }
    }
}

void printshudo()        //�������Ļ
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

void printshudotxt()        //�����sudotiku.txt
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
    srand((unsigned)time(NULL));    //��������Ӻ��� Ϊrand�����ṩ��ͬ������ ÿ�����г��������ͬ�������,��Ȼrand����ÿ�����г�����������������һ����
    ocout.open("sudoku.txt");
    cout<<"����������������Ŀ����N (0 < N <= 1000000):"<<endl;
    int N;
    cin>>N;
    cout<<"�������"<<N<<"�����ظ����ѽ����ϵ�������������:"<<endl;
    ocout << "�������"<<N<<"�����ظ����ѽ����ϵ�������������:" << endl;
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