#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

// ---------------- PCB ----------------
struct PCB {
    int JID, TTL, TLL;
    PCB(int jid=0,int ttl=0,int tll=0){
        JID=jid; TTL=ttl; TLL=tll;
    }
};

// ---------------- GLOBALS ----------------
char M[300][4];
char IR[4], R[4];
int IC;
bool C;

int SI, PI, TI;
int PTR, RA;

int TTC, TLC;
int ptrPointer;
int pageCount;

vector<int> AllocateList;
unordered_map<int,int> VaToRa;

ifstream bReader;
ofstream bWriter;

PCB p1;

// ---------------- TRIM ----------------
string trim(string s){
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
    return s;
}

// ---------------- INIT ----------------
void INIT(){
    for(int i=0;i<300;i++)
        for(int j=0;j<4;j++)
            M[i][j]=' ';

    memset(IR,' ',4);
    memset(R,' ',4);

    IC=0; C=false;
    SI=PI=TI=0;
    TTC=TLC=0;
    RA=0;

    AllocateList.clear();
    VaToRa.clear();

    PTR = (rand()%30)*10;

    for(int i=PTR;i<PTR+10;i++){
        M[i][0]='0';
        M[i][2]='*';
        M[i][3]='*';
    }

    ptrPointer = PTR;
    pageCount=0;
    p1 = PCB();
}

// ---------------- ALLOCATE ----------------
int ALLOCATE(){
    int val;
    do{
        val = rand()%30;
    }while(find(AllocateList.begin(),AllocateList.end(),val)!=AllocateList.end());

    AllocateList.push_back(val);
    return val;
}

// ---------------- ADDRESS MAP ----------------
void ADDRESSMAP(int IC){
    if(IC%10==0 && IC!=0) pageCount++;

    int addr = (M[PTR+pageCount][2]-'0')*10 + (M[PTR+pageCount][3]-'0');
    RA = addr*10 + IC%10;
}

// ---------------- MAP ----------------
void MAP(int add){

    // 🔥 Operand validation
    if(!isdigit(IR[2]) || !isdigit(IR[3])){
        if(IR[0] != 'H'){
            PI = 2; // Operand Error
        }
        return;
    }

    if(IR[0]=='B' && IR[1]=='T'){
        RA = add;
        return;
    }

    if(VaToRa.count((add/10)*10)){
        RA = VaToRa[(add/10)*10]*10 + (add%10);
        return;
    }

    if((IR[0]=='G'&&IR[1]=='D') || (IR[0]=='S'&&IR[1]=='R')){
        int temp = ALLOCATE();
        VaToRa[(add/10)*10] = temp;

        M[ptrPointer][0]='1';
        M[ptrPointer][2]=(temp/10)+'0';
        M[ptrPointer][3]=(temp%10)+'0';
        ptrPointer++;

        RA = temp*10;
    }
    else{
        PI = 3; // Page fault
    }
}


int READ(int loc){
    string data;
    getline(bReader,data);

    if(data.find("$END")!=string::npos){
        return -1;
    }

    int col=0;
    for(char c: data){
        M[loc][col%4]=c;
        col++;
        if(col%4==0) loc++;
    }
    return 1;
}


int WRITE(int loc){
    TLC++;
    if(TLC>p1.TLL) return -1;

    string out="";
    for(int i=loc;i<loc+10;i++){
        for(int j=0;j<4;j++)
            out+=M[i][j];
    }
    bWriter<<out<<endl;
    return 1;
}


void TERMINATE(string msg){
    bWriter<<"JOB ID:\t"<<p1.JID<<endl;
    bWriter<<msg<<endl;
    bWriter<<"IC:\t"<<IC<<endl;
    bWriter<<"TTC:\t"<<TTC<<endl;
    bWriter<<"TLC:\t"<<TLC<<endl<<"\n\n";
}


int MOS(int operand){
    if(TI==0){
        if(PI==1){ TERMINATE("Operation Code Error"); return -1;}
        if(PI==2){ TERMINATE("Operand Error"); return -1;}
        if(PI==3){ TERMINATE("Invalid Page Fault"); return -1;}

        if(SI==1) return READ(operand);
        if(SI==2) return WRITE(operand);
        if(SI==3){ TERMINATE("No Error"); return -1;}
    }
    else{
        TERMINATE("Time Limit Exceeded");
        return -1;
    }
    return 1;
}


void SIMULATION(){
    TTC++;
    if(TTC>p1.TTL) TI=2;
}


void EXECUTE(){
    IC=0;
    bool run=true;

    while(run){
        ADDRESSMAP(IC);

        memcpy(IR,M[RA],4);
        IC++;

        string opcode;
        if(IR[0]=='H') opcode="H";
        else{
            opcode.push_back(IR[0]);
            opcode.push_back(IR[1]);
        }

        int operand=(IR[2]-'0')*10+(IR[3]-'0');
        MAP(operand);
        operand=RA;

        if(opcode=="GD") SI=1;
        else if(opcode=="PD") SI=2;
        else if(opcode=="H"){ SI=3; run=false;}
        else if(opcode=="LR"){
            memcpy(R,M[operand],4);
        }
        else if(opcode=="SR"){
            memcpy(M[operand],R,4);
        }
        else if(opcode=="CR"){
            C = memcmp(R,M[operand],4)==0;
        }
        else if(opcode=="BT"){
            if(C) IC=operand;
        }
        else{
            PI=1;
        }

        SIMULATION();

        if(SI||PI||TI){
            if(MOS(operand)==-1) break;
            SI=PI=TI=0;
        }
    }
}

void LOAD(){
    string line;
    bool program=false;

    while(getline(bReader,line)){
        line = trim(line);

        if(line.empty()) continue;

        if(line.find("$AMJ")==0){
            INIT();

            int jid=stoi(line.substr(4,4));
            int ttl=stoi(line.substr(8,4));
            int tll=stoi(line.substr(12,4));
            p1 = PCB(jid,ttl,tll);

            program=true;
        }
        else if(line.find("$DTA")==0){
            EXECUTE();
        }
        else if(line.find("$END")==0){
            continue;
        }
        else if(program){

            int loc = ALLOCATE();

            M[ptrPointer][0]='1';
            M[ptrPointer][2]=(loc/10)+'0';
            M[ptrPointer][3]=(loc%10)+'0';
            ptrPointer++;

            int row=loc*10, col=0;

            // 🔥 FIX: Ensure 4-char alignment
            while(line.length()%4!=0) line+=' ';

            for(char c: line){
                M[row][col]=c;
                col++;
                if(col==4){
                    col=0;
                    row++;
                }
            }
        }
    }
}

int main(){
    bReader.open("input.txt");
    bWriter.open("output.txt");

    if(!bReader || !bWriter){
        cout<<"File error\n";
        return 0;
    }

    INIT();
    LOAD();

    bReader.close();
    bWriter.close();
}