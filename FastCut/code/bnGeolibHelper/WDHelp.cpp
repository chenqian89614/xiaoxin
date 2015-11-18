#include "WDHelp.h"

WDHelp::WDHelp(C2DPolygon qfy, BNPolyObject* bpoCurrMain)//, Point* allPoint, int numsPoint         C2DHoledPolygonSet
{
	//��ȡ���򲿷ֶ����
	C2DPolygon cp1=qfy;
	//����ཻ������б�
	C2DHoledPolygonSet chps;
	//�����򲿷��и���������ԭ������Ľ�
	cp1.GetOverlaps(*(bpoCurrMain->cp),chps);


	this->numsAllCP = chps.size();//��ȡ�ж��ٸ������
	for(int i=0;i<numsAllCP;i++)
	{
		//ȡ��һ������
		C2DHoledPolygon* chp=chps.GetAt(i);
		//��ȡ������״�����
		C2DPolygon* cpTemp=chp->GetRim();

		C2DPointSet pointCopy12;
		cpTemp->GetPointsCopy(pointCopy12);//��������״�����cpTemp�ĵ����ݸ�ֵ��pointCopy12
		allCP.push_back(C2DPolygon(pointCopy12, false));//�����ж����Vector���C2DPolygon����
	}
	if(numsAllCP == 1)//�������ֻ��һ��
	{
		onlyOneCP = (chps.GetAt(0))->GetRim();//��ȡ��ǰ��״�����
		onlyOneCP->GetPointsCopy(pointCopy);//��������״�����onlyOneCP�ĵ����ݸ�ֵ��pointCopy
	}
}

void WDHelp::Separate(IsNotCut* inc, C2DPointSet pointCopyIn)
{
	C2DPolygon cpTemp(pointCopyIn,  false);
	if(inc->pointSize/2 == this->numsAllCP)//��ͨ���иֻ�������������򣬼������и������bug���и�����߶��и�ʱ������ְ���ֱ��ȥ�и��bug����
	{
		std::vector<C2DPolygon>::iterator it = (this->allCP).begin();
		for(; it != (this->allCP).end(); it++)
		{
			C2DPolygon itcp = *it;
			flyCP.push_back(itcp);//��allCP�е�������ӵ�flyCP��Vector��

		}
		cpTemp.GetPointsCopy(pointCopy);//��cpTemp�еĵ����ݸ���pointCopy��
		return;
	}


	//�ж����еĶ����  Ӧ���Ƿ��ߵ�  ���ǲ����ߵ�     �����и�ʱ  �ĵ���    ---- ����и��ʱ�򣬰���ֱ���и��bug
	std::vector<C2DPolygon>::iterator it = (this->allCP).begin();
	for(; it != (this->allCP).end(); it++)
	{
		//��ȡ�˴ζ���ε����еĵ�
		C2DPointSet pointCopyF;
		C2DPolygon itcp = *it;
		itcp.GetPointsCopy(pointCopyF);//��ȡ�˴ζ���ε����еĵ�
		//��ȡ���������
		int tempC=pointCopyF.size();
		//������������
//		Point pArray[tempC];
		Point* pArray=new Point[tempC];
		for(int j=0;j<tempC;j++)//������εĵ�����ת��Ϊ��������pArray
		{
			C2DPoint* tempCP=pointCopyF.GetAt(j);
			pArray[j]=Point(tempCP->x,tempCP->y);
		}

		//=====��ȡ���==
		//---��������ε����еĵ㣬�� ��   �����߶������Ľ���   �Ƿ����ص�
		bool flag=false;//��־λ  Ϊfalse��ʾû���غϵ�
		for(int j=0;j<tempC;j++)//������������е�
		{
			std::vector<Point>::iterator jiaoDianIter= (inc->jiaoDian).begin();
			for(; jiaoDianIter !=  (inc->jiaoDian).end(); jiaoDianIter++)
			{
				if(pArray[j].fuzzyEquals((*jiaoDianIter),0.01)==true)//�����õ��˵��ģ���Ƚϣ��ж϶���εĵ����и��֮���Ƿ��0.01�����ڴ˷�Χ�ڣ�����Ϊ����֮�����
				{
					flag = true;//����־λ��Ϊtrue
					break;
				}
			}
			if(flag == true)//����־λ�Ѿ�Ϊtrue������Ҫ�ٱ���������ˣ����ٳ�������ʱ��
			{
				break;
			}
		}
//		delete pArray;//ɾ��ָ�򶥵������ָ��
		if(flag == false)
		{
			noFlyCP.push_back(itcp);//��itcp��ӵ���Ҫ���ߵĶ���ε�Vector
		}
		else
		{
			flyCP.push_back(itcp);//��itcp��ӵ�Ҫ���ߵĶ���ε�Vector
		}
	}

	C2DPolygon answerCP(pointCopyIn,false);
	//��ȡ���������
	int numsCpTemp=pointCopyIn.size();
	//������������
//	Point pArray1[numsCpTemp];
	Point* pArray1=new Point[numsCpTemp];
	//��֤����  �ǰ� ˳ʱ�� ���е�
	if(answerCP.IsConvex())//���������͹�����    ������ΪʲôҪ���ж�ΪʲôҪ���ж��ǲ���͹����Σ���ϸ��124��133�еĴ��룬һ�����Ŷ����ݵģ�һ�����Ŷ����ݵģ����п��Կ�����͹����ζ������ݺ�����˳ʱ��������ģ�������ε���������ʱ��ģ���ֻҪ֪���������߶�������˳���ǲ�ͬ�ľ����ˣ�
	{
		//˳ʱ���򶥵����鸳ֵ
		for(int j=0;j<numsCpTemp;j++)
		{
			C2DPoint* tempCP1=pointCopyIn.GetAt(j);
			pArray1[j]=Point(tempCP1->x,tempCP1->y);
		}
	}
	else
	{
		//��ʱ���붥�����鸳ֵ
		for(int j=0;j<numsCpTemp;j++)
		{
			C2DPoint* tempCP1=pointCopyIn.GetAt(numsCpTemp-1-j);
			pArray1[j]=Point(tempCP1->x,tempCP1->y);
		}
	}

	Zuhe(pArray1,numsCpTemp);//���µ�������ϣ���Ҫ�ǽ�pArray1�ж���ĵ��޳���
//	delete pArray1;
	return;
}
void WDHelp::Zuhe(Point* pArray1,int numsCpTemp)//����pArray1�����鳤��numsCpTemp
{
	//���¼�������õ�answer����
	Point answer[100];
	for(int j=0;j<numsCpTemp;j++)
	{
		answer[j] = pArray1[j];//��pArray1��������ݱ�����answer������
	}

	int numP = numsCpTemp;//������
	std::vector<C2DPolygon>::iterator iter1  = noFlyCP.begin();
	for(; iter1 !=  noFlyCP.end(); iter1++)//��  ����Ҫ�ɵĶ����  ����
	{
		C2DPointSet pointCopy2;
		(*iter1).GetPointsCopy(pointCopy2);
		//��ȡ���������
		int nums=pointCopy2.size();
		//������������
//		Point pArray2[nums];
		Point* pArray2=new Point[nums];
		//��֤������˳ʱ�����е�????    ����������ΪʲôҪ���ж�ΪʲôҪ���ж��ǲ���͹����Σ���ϸ��164��173�еĴ��룬һ�����Ŷ����ݵģ�һ�����Ŷ����ݵģ����п��Կ�����͹����ζ������ݺ�����˳ʱ��������ģ�������ε���������ʱ��ģ���ֻҪ֪���������߶�������˳���ǲ�ͬ�ľ����ˣ�
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

		//-------���----------
		Point tempAnswer[100];//������¼��ʱ�Ĵ�����
		int indexAnswer = -1;//��ʱ���������������
		for(int ii=0;ii<numP;ii++)//�� ��ǰ������ ���б���
		{
			bool flag = false;//��־λ
			for(int jj=0;jj<nums;jj++)//�� ��ǰ����εĵ����� ���б���
			{
				if(answer[ii]==pArray2[jj])//�� ��ǰ�𰸵�  �����εĵ�ǰ��  ����ͬ��
				{
					flag = true;
					indexAnswer++;
					tempAnswer[indexAnswer]=answer[ii];//�ѵ�ǰ����� tempAnswer��
					int indexii;
					//��indexii��ֵΪ  ����εĵ�ǰ�����������һ����
					if(jj==0)//����ǰ���������0����indexii��ֵΪ���鳤��-1
						indexii = nums-1;
					else
						indexii = jj - 1;
					if(answer[(ii+1)%numP]==pArray2[indexii])//��ǰ��� ��һ��  ��  ����εĵ�ǰ�����һ��   ����ͬ�� ���򽫶���εĲ��ֵ���ӵ�tempAnswer������
					{
						for(int kk=(jj+1)%nums;;kk=(kk+1)%nums)//����pArray2����
						{
							if(pArray2[kk] == pArray2[indexii])//�����forѭ������ֹ����  ���� ����εĵ�ǰ�����һ�� ��  �������ĵ���ͬʱ��
							{
								break;
							}
							indexAnswer++;
							tempAnswer[indexAnswer]=pArray2[kk];//������ӵ���������
						}
					}
				}
			}
			if(flag == false)
			{
				indexAnswer++;//�������1
				tempAnswer[indexAnswer]=answer[ii];//����ʱ�����鸳ֵ
			}
		}
//		delete pArray2;
		if(indexAnswer+1==numsCpTemp)
		{
			//����ȡ����ʱ�����鸳��answer����
			for(int k=0;k<numsCpTemp;k++)
			{
				answer[k] = tempAnswer[numsCpTemp-1-k];
			}
			iter1--;
			continue;//������   ����Ҫ�ɵĶ����  ����
		}


		numP = indexAnswer+1;
		//����ȡ����ʱ�����鸳��answer����
		for(int k=0;k<numP;k++)
		{
			answer[k] = tempAnswer[k];
		}
	}

	for(int jj=0;jj<pointCopy.size();jj++)//����pointCopy�е����е�
	{
		C2DPoint* tempCP=pointCopy.GetAt(jj);//��ȡ��
		pointCopy.DeleteAndSet(jj, tempCP);//��pointCopy��ɾ����
	}
	//��������pointCopy�еĵ�
	for(int j=0;j<numP;j++)
	{
		pointCopy.AddCopy(answer[j].x,answer[j].y);//���������еĵ������pointCopy
	}
}
