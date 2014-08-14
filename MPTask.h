#ifndef MPTASK_H
#define MPTASK_H

#include <rtm/RTC.h>



#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>


#include "MultipleOrderedEC.h"
#include "MPComp.h"


/*
*同一スレッドでの実行順序クラス
*/
class MPComp
{
public:
	MPComp(){};
	sub_Rule *comp;
	int I;
	int J;
	int K;
};

/*
*直列ブロックを実行するスレッドのクラス
*/
class MPTask : public virtual coil::Task
{
public:
		MPTask(RTC::MultipleOrderedEC *c);
		/*
		*スレッド実行関数
		*/
		virtual int svc();
		/*
		*コンポーネントを追加する関数
		*/
		void addComp(sub_Rule *c, int I, int J, int K);
private:
	std::vector<MPComp> m_comp;
	RTC::MultipleOrderedEC *m_ec;

};




#endif
