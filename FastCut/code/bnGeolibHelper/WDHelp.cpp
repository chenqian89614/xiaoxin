#include "WDHelp.h"

WDHelp::WDHelp(C2DPolygon qfy, BNPolyObject* bpoCurrMain)//, Point* allPoint, int numsPoint         C2DHoledPolygonSet
{
	//获取有球部分多边形
	C2DPolygon cp1=qfy;
	//存放相交区域的列表
	C2DHoledPolygonSet chps;
	//求有球部分切割用区域与原有区域的交
	cp1.GetOverlaps(*(bpoCurrMain->cp),chps);


	this->numsAllCP = chps.size();//获取有多少个多边形
	for(int i=0;i<numsAllCP;i++)
	{
		//取出一个区域
		C2DHoledPolygon* chp=chps.GetAt(i);
		//获取区域形状多边形
		C2DPolygon* cpTemp=chp->GetRim();

		C2DPointSet pointCopy12;
		cpTemp->GetPointsCopy(pointCopy12);//将区域形状多边形cpTemp的点数据赋值给pointCopy12
		allCP.push_back(C2DPolygon(pointCopy12, false));//向所有多边形Vector添加C2DPolygon对象
	}
	if(numsAllCP == 1)//若多边形只有一个
	{
		onlyOneCP = (chps.GetAt(0))->GetRim();//获取当前形状多边形
		onlyOneCP->GetPointsCopy(pointCopy);//将区域形状多边形onlyOneCP的点数据赋值给pointCopy
	}
}

void WDHelp::Separate(IsNotCut* inc, C2DPointSet pointCopyIn)
{
	C2DPolygon cpTemp(pointCopyIn,  false);
	if(inc->pointSize/2 == this->numsAllCP)//若通过切割，只产生了两个区域，即正常切割（不出现bug的切割，（用线段切割时，会出现按照直线去切割的bug））
	{
		std::vector<C2DPolygon>::iterator it = (this->allCP).begin();
		for(; it != (this->allCP).end(); it++)
		{
			C2DPolygon itcp = *it;
			flyCP.push_back(itcp);//将allCP中的所有添加到flyCP的Vector里

		}
		cpTemp.GetPointsCopy(pointCopy);//将cpTemp中的点数据赋给pointCopy里
		return;
	}


	//判断所有的多边形  应该是飞走的  还是不飞走的     根据切割时  的点数    ---- 解决切割的时候，按照直线切割的bug
	std::vector<C2DPolygon>::iterator it = (this->allCP).begin();
	for(; it != (this->allCP).end(); it++)
	{
		//获取此次多边形的所有的点
		C2DPointSet pointCopyF;
		C2DPolygon itcp = *it;
		itcp.GetPointsCopy(pointCopyF);//获取此次多边形的所有的点
		//获取顶点的数量
		int tempC=pointCopyF.size();
		//创建顶点数组
//		Point pArray[tempC];
		Point* pArray=new Point[tempC];
		for(int j=0;j<tempC;j++)//将多边形的点数据转化为顶点数组pArray
		{
			C2DPoint* tempCP=pointCopyF.GetAt(j);
			pArray[j]=Point(tempCP->x,tempCP->y);
		}

		//=====获取完毕==
		//---遍历多边形的所有的点，看 与   划得线而产生的交点   是否有重的
		bool flag=false;//标志位  为false表示没有重合的
		for(int j=0;j<tempC;j++)//遍历多边形所有点
		{
			std::vector<Point>::iterator jiaoDianIter= (inc->jiaoDian).begin();
			for(; jiaoDianIter !=  (inc->jiaoDian).end(); jiaoDianIter++)
			{
				if(pArray[j].fuzzyEquals((*jiaoDianIter),0.01)==true)//这里用到了点的模糊比较，判断多边形的点与切割点之间是否差0.01，若在此范围内，则认为两者之间相等
				{
					flag = true;//将标志位设为true
					break;
				}
			}
			if(flag == true)//若标志位已经为true，则不需要再遍历多边形了，减少程序运行时间
			{
				break;
			}
		}
//		delete pArray;//删除指向顶点数组的指针
		if(flag == false)
		{
			noFlyCP.push_back(itcp);//将itcp添加到不要飞走的多边形的Vector
		}
		else
		{
			flyCP.push_back(itcp);//将itcp添加到要飞走的多边形的Vector
		}
	}

	C2DPolygon answerCP(pointCopyIn,false);
	//获取顶点的数量
	int numsCpTemp=pointCopyIn.size();
	//创建顶点数组
//	Point pArray1[numsCpTemp];
	Point* pArray1=new Point[numsCpTemp];
	//保证数据  是按 顺时针 排列的
	if(answerCP.IsConvex())//若多边形是凸多边形    （下面为什么要先判断为什么要先判断是不是凸多边形，仔细看124和133行的代码，一个正着读数据的，一个反着读数据的，从中可以看出，凸多边形读的数据好像是顺时针读出来的，凹多边形的数据是逆时针的，你只要知道反正两者读出来的顺序是不同的就行了）
	{
		//顺时针向顶点数组赋值
		for(int j=0;j<numsCpTemp;j++)
		{
			C2DPoint* tempCP1=pointCopyIn.GetAt(j);
			pArray1[j]=Point(tempCP1->x,tempCP1->y);
		}
	}
	else
	{
		//逆时针想顶点数组赋值
		for(int j=0;j<numsCpTemp;j++)
		{
			C2DPoint* tempCP1=pointCopyIn.GetAt(numsCpTemp-1-j);
			pArray1[j]=Point(tempCP1->x,tempCP1->y);
		}
	}

	Zuhe(pArray1,numsCpTemp);//留下的重新组合（主要是将pArray1中多余的点剔除）
//	delete pArray1;
	return;
}
void WDHelp::Zuhe(Point* pArray1,int numsCpTemp)//数组pArray1，数组长度numsCpTemp
{
	//起记录保存作用的answer数组
	Point answer[100];
	for(int j=0;j<numsCpTemp;j++)
	{
		answer[j] = pArray1[j];//将pArray1数组的数据保存至answer数组中
	}

	int numP = numsCpTemp;//顶点数
	std::vector<C2DPolygon>::iterator iter1  = noFlyCP.begin();
	for(; iter1 !=  noFlyCP.end(); iter1++)//对  不需要飞的多边形  遍历
	{
		C2DPointSet pointCopy2;
		(*iter1).GetPointsCopy(pointCopy2);
		//获取顶点的数量
		int nums=pointCopy2.size();
		//创建顶点数组
//		Point pArray2[nums];
		Point* pArray2=new Point[nums];
		//保证数据是顺时针排列的????    （不懂下面为什么要先判断为什么要先判断是不是凸多边形，仔细看164和173行的代码，一个正着读数据的，一个反着读数据的，从中可以看出，凸多边形读的数据好像是顺时针读出来的，凹多边形的数据是逆时针的，你只要知道反正两者读出来的顺序是不同的就行了）
		if((*iter1).IsConvex())
		{
			for(int j=0;j<nums;j++)
			{
				C2DPoint* tempCP1=pointCopy2.GetAt(j);
				pArray2[j]=Point(tempCP1->x,tempCP1->y);
			}
		}
		else
		{
			for(int j=0;j<nums;j++)
			{
				C2DPoint* tempCP1=pointCopy2.GetAt(nums-1-j);
				pArray2[j]=Point(tempCP1->x,tempCP1->y);
			}
		}

		//-------组合----------
		Point tempAnswer[100];//用来记录临时的答案数组
		int indexAnswer = -1;//临时答案数组的数组索引
		for(int ii=0;ii<numP;ii++)//对 当前答案数组 进行遍历
		{
			bool flag = false;//标志位
			for(int jj=0;jj<nums;jj++)//对 当前多边形的点数组 进行遍历
			{
				if(answer[ii]==pArray2[jj])//若 当前答案点  与多边形的当前点  是相同的
				{
					flag = true;
					indexAnswer++;
					tempAnswer[indexAnswer]=answer[ii];//把当前点加入 tempAnswer中
					int indexii;
					//将indexii赋值为  多边形的当前点的索引的上一索引
					if(jj==0)//若当前点的索引是0，则将indexii赋值为数组长度-1
						indexii = nums-1;
					else
						indexii = jj - 1;
					if(answer[(ii+1)%numP]==pArray2[indexii])//当前点的 下一点  与  多边形的当前点的上一点   是相同的 ，则将多边形的部分点添加到tempAnswer数组中
					{
						for(int kk=(jj+1)%nums;;kk=(kk+1)%nums)//遍历pArray2数组
						{
							if(pArray2[kk] == pArray2[indexii])//这个是for循环的终止条件  （当 多边形的当前点的上一点 与  遍历到的点相同时）
							{
								break;
							}
							indexAnswer++;
							tempAnswer[indexAnswer]=pArray2[kk];//将点添加到答案数组中
						}
					}
				}
			}
			if(flag == false)
			{
				indexAnswer++;//答案数组加1
				tempAnswer[indexAnswer]=answer[ii];//给临时答案数组赋值
			}
		}
//		delete pArray2;
		if(indexAnswer+1==numsCpTemp)
		{
			//将获取的临时答案数组赋给answer数组
			for(int k=0;k<numsCpTemp;k++)
			{
				answer[k] = tempAnswer[numsCpTemp-1-k];
			}
			iter1--;
			continue;//继续对   不需要飞的多边形  遍历
		}


		numP = indexAnswer+1;
		//将获取的临时答案数组赋给answer数组
		for(int k=0;k<numP;k++)
		{
			answer[k] = tempAnswer[k];
		}
	}

	for(int jj=0;jj<pointCopy.size();jj++)//遍历pointCopy中的所有点
	{
		C2DPoint* tempCP=pointCopy.GetAt(jj);//获取点
		pointCopy.DeleteAndSet(jj, tempCP);//从pointCopy中删除点
	}
	//重新设置pointCopy中的点
	for(int j=0;j<numP;j++)
	{
		pointCopy.AddCopy(answer[j].x,answer[j].y);//将答案数组中的点增添给pointCopy
	}
}
