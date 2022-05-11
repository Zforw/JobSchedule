#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;
struct job {
	int get;
	int run;
	int id;
};
int n = 10;
bool cmp(job a, job b)//按照到达时间进行排序
{
	return a.get < b.get;
}
struct cpu {
	int job;
	int rem;
} cpu1, cpu2;
job zy[100];
int cnt = 0;
double w = 0, dw = 0;
int t = 0;
bool use[100];
void init() {
	cpu1.job = -1;cpu1.rem = 0;
	cpu2.job = -1;cpu2.rem = 0;
	memset(use, 0, sizeof(use));
	cnt = 0;t = 0;w = 0;dw = 0;
}
void run(cpu & c, int job) {
	if(c.job == -1) {
		//cpu空闲
		if(job != -1) {
			//当前有待处理的作业
			c.job = job;
			c.rem =  zy[job].run;
			use[job] = true;
			cout << char('A' + zy[c.job].id) << " ";
		}
	}
	c.rem--;//cpu执行
	if(c.rem == 0 && c.job != -1) {
		double wait = t - zy[c.job].get;
		double dwait = (double) wait / zy[c.job].run;
		w += wait;
		dw += dwait;
		c.job = -1;
		cnt++;
	}
}
void fcfs() {
	init();
	while(cnt < n) {
		int job = -1;
		for(int i = 0;i < n;i++) {
			if(zy[i].get <= t && use[i] == 0) {
				job = i;
				break;
			}
		}
		run(cpu1, job);
		job = -1;
		for(int i = 0;i < n;i++) {
			if(zy[i].get <= t && use[i] == 0) {
				job = i;
				break;
			}
		}
		run(cpu2, job);
		t++;
	}
	w = w / n*1.0;
	dw = dw / n*1.0;
	cout << endl << "先来先服务算法的平均周转时间是： " << w << " 带权平均周转时间是：" << dw << endl;
}
void sjfs() {
	init();
	while(cnt < n) {
		int job = -1;
		int min_run = 1000;
		for(int i = 0;i < n;i++) {
			if(use[i] == 0 && zy[i].get <= t && zy[i].run < min_run) {
				job = i;
				min_run = zy[job].run;
			}
		}
		run(cpu1, job);
		job = -1;
		min_run = 1000;
		for(int i = 0;i < n;i++) {
			if(use[i] == 0 && zy[i].get <= t && zy[i].run < min_run) {
				job = i;
				min_run = zy[job].run;
			}
		}
		run(cpu2, job);
		t++;
	}
	w = w / n*1.0;
	dw = dw / n*1.0;
	cout << endl << "短作业优先算法的平均周转时间是： " << w << " 带权平均周转时间是：" << dw << endl;
}
void hrrf() {
	init();
	//响应比=等待时间/运行时间+1
	while(cnt < n) {
		int job = -1;
		double call = -1000;
		for(int i = 0;i < n;i++) {
			if(use[i] == 0 && zy[i].get <= t && ((double)(t - zy[i].get) / zy[i].run) + 1 > call) {
				job = i;
				call = ((double)(t - zy[i].get) / zy[i].run) + 1;
			}
		}
		run(cpu1, job);
		job = -1;
		call = -1000;
		for(int i = 0;i < n;i++) {
			if(use[i] == 0 && zy[i].get <= t && ((double)(t - zy[i].get) / zy[i].run) + 1 > call) {
				job = i;
				call = ((double)(t - zy[i].get) / zy[i].run) + 1;
			}
		}
		run(cpu2, job);
		t++;
	}
	w = w / n*1.0;
	dw = dw / n*1.0;
	cout << endl << "响应比高者优先算法的平均周转时间是： " << w << " 带权平均周转时间是：" << dw << endl;
}
int main() {
	ifstream in("input.txt");
	for (int i = 0; i < n; i++)
	{
		in >> zy[i].get;
		zy[i].id = i;
	}
	for (int i = 0; i < n; i++)
	{
		in >> zy[i].run;
	}
	sort(zy, zy + n, cmp);
	for(int i = 0;i < n;i++) {
		cout << setw(2) << char('A' + zy[i].id) << " ";
	}
	cout << endl;
	for(int i = 0;i < n;i++) {
		cout << setw(2) << zy[i].get << " ";
	}
	cout << endl;
	for(int i = 0;i < n;i++) {
		cout << setw(2) << zy[i].run << " ";
	}
	cout << endl << endl;
	fcfs();
	sjfs();
	hrrf();
	return 0;
}
/*
		if(cpu1.job == -1) {
			//cpu1空闲
			if(job != -1) {
				//当前有待处理的作业
				cpu1.job = job;
				cpu1.rem =  zy[job].run;
				cpu1.rem--;
				use[job] = true;
				cout << char('A' + zy[cpu1.job].id) << " ";
			}
		} else {
			//cpu1执行
			cpu1.rem--;
			if(cpu1.rem == 0) {
				wait = t - zy[cpu1.job].get;
				dwait = (double) wait / zy[cpu1.job].run;
				w += wait;
				dw += dwait;
				cpu1.job = -1;
				cnt++;
			}
		}
		if(cpu2.job == -1) {
			//cpu2空闲
			if(job != -1) {
				//当前有待处理的作业
				cpu2.job = job;
				cpu2.rem =  zy[job].run;
				cpu2.rem--;
				use[job] = true;
				cout << char('A' + zy[cpu2.job].id) << " ";
			}
		} else {
			//cpu2执行
			cpu2.rem--;
			if(cpu2.rem == 0) {
				wait = t - zy[cpu2.job].get;
				dwait = (double) wait / zy[cpu2.job].run;
				w += wait;
				dw += dwait;
				cpu2.job = -1;
				cnt++;
			}
		}
		 */