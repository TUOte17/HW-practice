 #include "dask.h" 
DiskArm::DiskArm(){ 
std::cout << "Please input current Cylinder:"; 
std::cin >> CurrentCylinder; 
//磁头⽅向 
// 0 ：向⼩磁道号⽅向移动 
// 1 ：向⼤磁道号⽅向移动 
std::cout << "Please input current direction (0/1):"; 
std::cin >> SeekDirection; 
//输入磁盘请求数，请求道号 
std::cout << "Please input request numbers:"; 
std::cin >> RequestNumber; 
std::cout << "Please input request cylinder string:"; 
  Request = new int[sizeof(int) * RequestNumber]; 
  Cylinder = new int[sizeof(int) * RequestNumber]; 
for (int i = 0; i < RequestNumber; i++) 
std::cin >> Request[i]; 
} 
DiskArm::~DiskArm(){ 
} 
//初始化道号，寻道记录
void DiskArm::InitSpace(char *MethodName) { 
std::cout << std::endl << MethodName << std::endl; 
  SeekNumber = 0; 
  SeekChange = 0; 
for (int i = 0; i < RequestNumber; i++) 
    Cylinder[i] = Request[i]; 
} 
//统计报告算法执⾏情况
void DiskArm::Report() { 
std::cout << std::endl; 
std::cout << "Seek Number:" << SeekNumber << std::endl; 
std::cout << "Change Direction :" << SeekChange << std::endl << std::endl; 
} 
void DiskArm::FCFS() { 
int Current = CurrentCylinder; 
int Direction = SeekDirection; 
  InitSpace("FCFS"); 
std::cout << Current; 
for (int i = 0; i < RequestNumber; i++) { 
bool needChangeDirection = ((Cylinder[i] >= Current)&&!Direction) ||((Cylinder[i] < Current) && Direction); 
if (needChangeDirection) { 
      Direction = !Direction; 
      SeekChange ++; //调头数加1 
//报告当前响应的道号 
std::cout << std::endl << Current << "->" << Cylinder[i]; 
    } 
    
else { 
//不需要调头，报告当前响应的道号 
std::cout << "->" << Cylinder[i]; 
//累计寻道数，响应过的道号变为当前道号 
    SeekNumber += abs(Current - Cylinder[i]); 
    Current = Cylinder[i]; 
  }
} 
//报告磁盘调度情况 
  Report(); 
} 
void DiskArm::SSTF(){ 
    int Current = CurrentCylinder; 
    int Direction = SeekDirection; 
    InitSpace("SSTF"); 
    std::cout << Current;
    int *p=new int[RequestNumber];
    for (int i = 0; i < RequestNumber; i++){
        p[i]=Cylinder[i];
    }
    for (int i = 0; i < RequestNumber; i++){ 
    int Minseek = 9999;
    int j;
    for(int k=0;k<RequestNumber;k++){
        if (Minseek>abs(p[k]-Current)){
            j=k;
            Minseek=abs(p[k]-Current);
        }
    }//寻找路径最短的点
    bool needChangeDirection = ((Cylinder[j] >= Current)&&!Direction)|| ((Cylinder[j] < Current) && Direction); 
    if (needChangeDirection) { 
        Direction = !Direction; 
        SeekChange ++; //调头数加1 
        std::cout << std::endl << Current << "->" << Cylinder[j]; 
    } 
    
else { 
std::cout << "->" << Cylinder[j]; 
//累计寻道数，响应过的道号变为当前道号 
    
  }SeekNumber += Minseek; 
  Current = Cylinder[j]; 
  p[j]=-9999;
} 
//报告磁盘调度情况
  delete p;
  Report(); 
} 

void DiskArm::SCAN(){ 
    int Current = CurrentCylinder; 
    int Direction = SeekDirection; 
    InitSpace("SCAN"); 
    std::cout << Current;
    int *p=new int[RequestNumber];
    int temp;
    for (int i = 0; i < RequestNumber; i++)
        p[i]=Cylinder[i];
     for(int i=0;i<2;i++){ 
        std::cout << std::endl << Current;   
        for(;Direction?Current<200:Current>0;Direction?Current++:Current--){
            for(int j=0;j<RequestNumber;j++){
                if(p[j]==Current){
                std::cout << "->" << Cylinder[j];
                p[j]=-1;}
            }
            SeekNumber++;
        }
        std::cout << "->" << Current;
        Direction=!Direction;
     }
     SeekChange=1;
//报告磁盘调度情况
  delete p;
  Report(); 
} 

void DiskArm::CSCAN(){ 
int Current = CurrentCylinder; 
    int Direction = SeekDirection; 
    InitSpace("CSCAN"); 
    std::cout << Current;
    int *p=new int[RequestNumber];
    int temp=0;
    for (int i = 0; i < RequestNumber; i++)
        p[i]=Cylinder[i];
     for(int i=0;i<2;i++){ 
        std::cout << std::endl << Current;   
        for(;Direction?Current<200:Current>0;Direction?Current++:Current--){
            for(int j=0;j<RequestNumber;j++){
                if(p[j]==Current){
                std::cout << "->" << Cylinder[j];
                p[j]=-1;
                temp++; 
            }
            }if(temp==RequestNumber)
                break;
            SeekNumber++;
            
        }
        if(i!=1)
        std::cout << "->" << Current;
        Current=Direction?0:200;
     }
     SeekChange=1;
//报告磁盘调度情况
  delete p;
  Report();
} 
void DiskArm::LOOK(){ 
    int Current = CurrentCylinder; 
    int Direction = SeekDirection; 
    InitSpace("LOOK"); 
    std::cout << Current;
    int *p=new int[RequestNumber];
    int temp;
    for (int i = 0; i < RequestNumber; i++)
        p[i]=Cylinder[i];
    for (int i = 0; i < RequestNumber - 1; i++){
                for (int j = 0; j < (RequestNumber - 1 - i); j++)
                        if (p[j] > p[j + 1]){
                            temp =p[j];
                            p[j]=p[j+1];
                            p[j+1]=temp;
                        }
     }
     int Max=p[RequestNumber-1];
     for(int i=0;i<2;i++){ 
        std::cout << std::endl << Current;   
        for(;Direction?Current<Max:Current>0;Direction?Current++:Current--){
            for(int j=0;j<RequestNumber;j++){
                if(p[j]==Current){
                std::cout << "->" << p[j];
                p[j]=-1;
            }
        }
            SeekNumber++;
            
        }
        if(i!=1)
        std::cout << "->" << Current;
        Direction=!Direction;
     }
     SeekChange=1;
//报告磁盘调度情况
  delete p;
  Report();
}
int main(){
    DiskArm a;
    a.FCFS();
    a.SSTF();
    a.SCAN();
    a.CSCAN();
    a.LOOK();
    system("pause");
}