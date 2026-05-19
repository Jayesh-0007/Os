#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

char M[100][4], IR[4];
int IC, TTL, TTC, jobId;

ifstream fin("input.txt");
ofstream fout("output.txt");

void init() {
    memset(M, ' ', sizeof(M));
    IC = TTC = 0;
}

void printMemory() {
    fout << "\nMEMORY TABLE (JOB " << jobId << ")\n";
    for (int i = 0; i < 20; i++) {
        fout << "M[" << i << "] : ";
        for (int j = 0; j < 4; j++) fout << M[i][j];
        fout << endl;
    }
}

void execute() {
    while (true) {

        if (TTC >= TTL) {
            fout << "JOB " << jobId << ": TIME LIMIT EXCEEDED\n\n";
            return;
        }

        memcpy(IR, M[IC], 4);
        IC++; TTC++;

        int addr = (IR[2]-'0')*10 + (IR[3]-'0');

        if (IR[0]=='G' && IR[1]=='D') {
            string data;
            getline(fin >> ws, data);
            for (int i=0;i<data.size();i++)
                M[addr+i/4][i%4]=data[i];

            fout << "GD → Stored at " << addr << endl;
        }

        else if (IR[0]=='P' && IR[1]=='D') {
            fout << "PD → ";
            for (int i=0;i<40;i++){
                char ch = M[addr+i/4][i%4];
                if (ch==' '||ch=='\0') break;
                fout<<ch;
            }
            fout<<endl;
        }

        else if (IR[0]=='H') {
            fout << "HALT\n";
            printMemory();
            fout << endl;
            return;
        }
    }
}

void load() {
    string line; int m=0;

    while (getline(fin,line)) {
        if (line.substr(0,4)=="$AMJ") {
            init(); m=0;
            sscanf(line.c_str(),"$AMJ %d %d",&jobId,&TTL);
        }
        else if (line.substr(0,4)=="$DTA") execute();
        else if (line.substr(0,4)!="$END") {
            for(int i=0;i<line.size();i+=4){
                for(int j=0;j<4;j++)
                    M[m][j]=(i+j<line.size())?line[i+j]:' ';
                m++;
            }
        }
    }
}

int main() {
    load();
    cout << "Phase 1 Done\n";
}