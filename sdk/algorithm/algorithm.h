#include "PiTypeDef.h"
#include <math.h>
#include "Chain.h"

template <class T>
void Swap(T& a, T& b);


template <class T>
void SwapIfMax(T* arr, DWORD pos1, DWORD pos2);

template<class T>
DWORD Max(T* arr, DWORD pos1, DWORD pos2);

template<class T>
DWORD Max(T* arr, DWORD lCount);

template<class T>
DWORD MaxIn3(T* arr, DWORD pos1, DWORD pos2, DWORD pos3);

template<class T>
DWORD Min(T* arr, DWORD pos1, DWORD pos2);

template<class T>
bool isHeap(T* arr, DWORD parent, DWORD pos2, DWORD pos3);

template<class T>
void MergerGroup(T* arr, DWORD dwPos1, DWORD dwPos2, DWORD dwGroupSize, DWORD dwTwoGroupTotalSize);


template<class T>
void RadixSort(T* arr ,DWORD lCount);

byte GetValueLength(DWORD dwValue);

template<class T>
byte GetMaxDigitLen(T* arr ,DWORD lCount);

byte GetDigit(DWORD dwValue, byte byDigit);

/************************************************************************/
/* ֱ�Ӳ�������                                                         
 version: 1.0 ��2012-6-8 13:36:31  
 remark:	1. �״�ʵ�֣�����ȷ���򣬵������С��int���ͣ�Ӧ����DWORD���ͣ����򲻽��ܴ�����
			2. ÿ�ζ�ҪbNeedMove ��ʶ��θ�ֵ�ˣ����Ľ�
/************************************************************************/
// 10 2 5 17 4 
template <class T>
bool StraightInsertionSort(T* Arr ,DWORD lCount, DWORD dwPos = 1)
{
	//DWORD dwPos = 1;//Ԫ�ؼ�ļ��,ϣ��������Ҳ�����õ�
	DWORD dwSize = lCount;
	bool bNeedMove = false;
	for (DWORD i = dwPos;i<dwSize;i+= dwPos )
	{
		long j = i - dwPos ;
		bNeedMove = false;
		for(; j >= 0 && Arr[i] < Arr[j] ;j -= dwPos )
		{
			bNeedMove = true;
		}
		//���뵽λ�ã��Ӳ���λ�õ�֮ǰi - 1��Ԫ�ض������ƶ�
		T temp = Arr[i];
		j += dwPos ;//�����λ��
		if (bNeedMove)
		{
			for (int iMove = i; iMove> j; iMove -= dwPos)
			{
				Arr[iMove] = Arr[iMove - dwPos];
			}
			Arr[j] = temp;
		}
		
	}
	return true;
};

/************************************************************************/
/* function: ֱ��ѡ������     
    argm:1 - Ҫ����������׵�ַ, 2 - Ԫ�ظ���
/************************************************************************/
template<class T>
bool SimpleSelectionSort(T* arr ,DWORD lCount)
{
	DWORD i = 0;
	const T* pTemp = arr;
	for(;i < lCount;++i)
	{
		//��ȡ��С��Ԫ��index
		DWORD dwMinIndex = Min(pTemp + i, lCount - i);
		if (dwMinIndex + i != i)
		{
			Swap(arr[i], arr[dwMinIndex + i]);
		}
	}
	return true;
}


/************************************************************************/
/* ϣ������                                                                     */
/************************************************************************/
template<class T>
bool ShellSort(T* arr ,DWORD lCount)
{
	//�ȶ԰�ַ���, gPos = n/2; ÿ����������<= Ԫ�ظ���/2
	UNLONG dwPos = lCount/2;
	while(1)
	{
		
		//�Է�����ÿ�����ֱ�Ӳ�������
		for (UNLONG i = 0;i<dwPos;++i)
		{
			StraightInsertionSort(arr + i, lCount - i, dwPos);
		}
		if (1 == dwPos)
		{
			break;
		}
		dwPos = dwPos/2;
		// ���۰����, gPos = gPos/2;
		
	}
	
	return true;
}

/************************************************************************/
/* ������                                                                     */
/***********************************************************************/
template<class T>
void HeapSort(T* arr ,DWORD lCount)
{
    //����ʼ��
    BuildHeap(arr, lCount);

    //������    

	//�������ֵ������, �Ӻ��濪ʼһֱ�������ڶ���Ԫ��
	
	for (DWORD i = 1;i<lCount;++i)
	{
		Swap(arr[0], arr[lCount - i]);
		if(!isHeap(arr,0, 1, 2))
		{
			HeapAdjust(arr, 1, lCount - i);
		}
	}	
};


template<class T>
void BuildHeap(T* arr, DWORD lCount)
{
	for (UNLONG dwPos = lCount/2; dwPos > 0 ;--dwPos)
	{
		HeapAdjust(arr, dwPos,  lCount);
	}

}

template<class T>
void HeapAdjust(T* arr, DWORD NoteId, DWORD dwTotal)
{
	DWORD dwMaxIndex = dwTotal - 1;
	if(NoteId < 1)
	{
		return ;
	}
	UNLONG dwParent = NoteId - 1;
	UNLONG dwLChild = NoteId * 2 - 1;
	UNLONG dwRChild = NoteId * 2 + 1  - 1;

	dwRChild = (dwRChild > dwMaxIndex ) ? dwMaxIndex  : dwRChild;
	if (dwLChild <= dwMaxIndex  && dwRChild <= dwMaxIndex)
	{
		//�ҳ����ڵ�,�����Һ����е����ֵ
		UNLONG arrTemp[] = { arr[dwParent], arr[dwLChild], arr[dwRChild] };
		UNLONG dwMaxPos = MaxIn3(arr, dwParent, dwLChild, dwRChild);

		if (dwMaxPos != dwParent)
		{
			Swap(arr[dwParent], arr[dwMaxPos]);

			//������������к���, ҲҪ������
			if (dwMaxPos <= dwTotal/2)
			{
				HeapAdjust(arr, dwMaxPos + 1, dwTotal);
			}
		}
	}
}

/************************************************************************/
/*	fun: �ж��Ƿ�Ϊ��                                                                     */
/************************************************************************/
template<class T>
bool isHeap(T* arr, DWORD parent, DWORD pos2, DWORD pos3)
{
	return (arr[parent] > arr[pos2] ) && (arr[parent] > arr[pos3]);
}

/************************************************************************/
/*	fun:ð������                                                                   
	
/************************************************************************/
template<class T>
bool BubbleSort(T* arr, DWORD lCount)
{
	for (DWORD i = 0;i< lCount -1;++i)
	{
		SingleBubble(arr,lCount - i);
	}
	
	Max(arr, lCount);
	return true;
}

template<class T>
void SingleBubble(T* arr, DWORD dwUnSort)
{
	for (DWORD i = 0;i < dwUnSort - 1;++i)
	{
		DWORD dwMaxPos = Max(arr, i, i + 1);

		if(i == dwMaxPos)
		{
			//��Ҫ����
			Swap(arr[i], arr[i + 1]);
		}

	}
}

/************************************************************************/
/*	fun:��������                                                                   
	ret:�ݹ�ʵ��
/************************************************************************/
template<class T>
void QuickSort(T* arr, DWORD dwCount)
{
	if(dwCount < 2 )
	{
		return ;
	}

	DWORD dwBasePos = 0;//�ؼ����ݵ�����λ��
	DWORD dwComparePos = dwCount - 1;
	char cOffsetToNext = -1;
	bool bLeft = true;
	while(dwBasePos != dwComparePos)
	{
		if((arr[dwBasePos] > arr[dwComparePos]) == bLeft )
		{
			Swap(arr[dwBasePos], arr[dwComparePos]);
			cOffsetToNext = 0 - cOffsetToNext;//��һ��Ԫ�ص�ƫ�Ʊ�Ϊ�෴��
			bLeft  = !bLeft;//�ؼ�ֵ����һ��

			//����ָ��λ��,���Ƶ���һ�����Ƚ�λ��
			UNLONG dwTemp = dwComparePos;
			dwComparePos = dwBasePos + cOffsetToNext;
			dwBasePos = dwTemp;
		}
		else
		{
			dwComparePos +=  cOffsetToNext;
		}
	}
	
	//����ߺ��ұ߶��ֱ����һ�˿�������
	QuickSort(arr, dwBasePos);
	QuickSort(arr + dwBasePos + 1, dwCount -1 - dwBasePos);
}


/************************************************************************/
/*	fun:�鲢����                                                                   
	ret:�ȶ�����
/************************************************************************/

template<class T>
void MergerSort(T* arr, DWORD dwCount)
{
	DWORD dwCountPerGroup = 2;
	//DWORD dwMaxMergerCroupSize = ceil(dwCount/2.0) ; //����ȡ��
	for (DWORD dwGroupSize = 1;dwCount > dwGroupSize; dwGroupSize *=2)
	{
		MergerSortSingle(arr, dwCount, dwGroupSize);
	}
}

//����һ������������ ָ����С�ĺϲ�
template<class T>
void MergerSortSingle(T* arr, DWORD dwArrCount, DWORD dwGroupSize)
{
	//�ϲ���Ԫ��, mergeA �� mergeB
	DWORD dwNeedCount = ceil(ceil(dwArrCount/(double)dwGroupSize) / 2);//�ܹ���Ҫ���κϲ�,��һ�˲��ܺ���
	DWORD dwCount = 0;
	for (DWORD i = 0;i<dwArrCount;i += dwGroupSize * 2)
	{
		//�ж����һ����ϲ���������ǲ�������
		//DWORD dwTwoGroupSize = (dwGroupSize * 2);
		DWORD dwRemainder = dwArrCount % dwGroupSize;

		// ����ֵ�д�
		dwCount++;//��������˳��
		DWORD dwSecond = i +  dwGroupSize;//mergeB���ڵ�����
		DWORD dwLack = dwRemainder && (dwCount == dwNeedCount) ? dwGroupSize - dwRemainder : 0;
		bool bValid = dwSecond < dwArrCount;// ���ϲ����Ƿ�����2
		if (bValid)
		{
			MergerGroup(arr , i, i + dwGroupSize, dwGroupSize, dwLack);
		}
		
	}
}

template<class T>
void MergerGroup(T* arr, DWORD dwPos1, DWORD dwPos2, DWORD dwGroupSize, DWORD dwLack)
{
	//DWORD dwMaxIndex = dwGroupSize - 1;
	DWORD dwAfterMerger = dwGroupSize * 2 -dwLack;
	DWORD dwComparePos1 = dwPos1;
	DWORD dwComparePos2 = dwPos2;
	DWORD dwMoveTime1 = 0;
	DWORD dwMoveTime2 = 0;
	//�����ռ�����źϲ��������
	T* pMergerTemp = new T[dwAfterMerger];
	memset(pMergerTemp, 0, sizeof(T) * dwAfterMerger);
	DWORD i = 0;
	for (i = 0; i < dwAfterMerger && (dwMoveTime1 < dwGroupSize && dwMoveTime2 < dwGroupSize - dwLack) 
		;i += 1)
	{
		DWORD dwMaxPos = Min(arr, dwComparePos1, dwComparePos2);

		pMergerTemp[i] = arr[dwMaxPos];

		//�ƶ�ָ�뵽��һ��
		if (dwComparePos1 == dwMaxPos)
		{
			dwComparePos1++;
			++dwMoveTime1;
		}
		else
		{
			//Swap(arr[dwPos1 + dwComparePos1], arr[dwPos2 + dwComparePos1]);
			dwComparePos2++;
			++dwMoveTime2;
		}
	}
	DWORD dwMoveTotal = dwMoveTime1 + dwMoveTime2;



	//����и�ָ���Ƴ�������,��һ��ָ��ʣ�µ�����ֱ��׷�ӷ���
	if (dwMoveTotal < dwAfterMerger)
	{
		//��û�ƶ������,���²���ֱ�Ӹ��ƹ�ȥ
		DWORD dwRemainPos = 0;
		if(dwMoveTime1 < dwGroupSize)
		{
			dwRemainPos = dwComparePos1;
		}
		else
		{
			dwRemainPos = dwComparePos2;
		}
		//DWORD dwRemainPos = (dwMoveTime1 <= dwMoveTime2 )? dwComparePos1 : dwComparePos2;
		memcpy_s(pMergerTemp + dwMoveTotal, sizeof(T) * (dwAfterMerger - dwMoveTotal), arr + dwRemainPos, sizeof(T) * (dwAfterMerger - dwMoveTotal));
	}

	DWORD dwTemp = sizeof(T) * dwAfterMerger; 
	memcpy_s(arr + dwPos1, dwTemp, pMergerTemp, dwTemp);
	delete [] pMergerTemp;
	//dwGroupSize
}


/************************************************************************/
/*	fun:��������                                            
	remart: ֻ��������Ȼ��. �����漰���ַ�������,�����д��Ľ�
/***********************************************************************/
template<class T>
void RadixSort(T* arr ,DWORD lCount)
{
	byte byLen = GetMaxDigitLen(arr, lCount);//��Ҫ����
	for (byte i = 0;i<byLen;++i)
	{
		
		RadixSortSingle(arr, lCount, i);
	}
}

template<class T>
void RadixSortSingle(T* arr ,DWORD lCount, byte byRadix)
{
	//���丨���ռ�
	CChain<DWORD>* pChainArr = new CChain<DWORD>[10];// 0-9

	for (DWORD i = 0;i<lCount;++i)
	{
		byte byValue = GetDigit(arr[i], byRadix);
		
		pChainArr[byValue].Append(arr[i]);//�ŵ�������Ӧ��λ��
	}

	//��˳���Ƶ�ԭ���ڴ�, ʵ����Ԫ��˳��ĵ���
	DWORD dwCopyed = 0;
	for (DWORD i = 0;i<10;++i)// ���� 0-9
	{
		//pChainArr[i].m_pNode;
		dwCopyed += pChainArr[i].CopyAllToMemory(arr + dwCopyed);
	}
	delete [] pChainArr;
}
/************************************************************************/
/*	fun: ��ȡ ��ֵ�����λ����
/************************************************************************/
template<class T>
byte GetMaxDigitLen(T* arr ,DWORD lCount)
{
	DWORD dwMaxValue = arr[Max(arr, lCount)];
	return GetValueLength(dwMaxValue);
	
}

/************************************************************************
	fun: ��ȡһ�������м�λ                                     
***********************************************************************/
byte GetValueLength(DWORD dwValue)
{
	char cTemp[30] = {0};
	_itoa_s(dwValue, cTemp, _countof(cTemp), 10);
	return strlen(cTemp);
	
}
/************************************************************************/
/*	fun:��ȡָ��λ����ֵ, ��λ=0, ʮλ=1, 
	remark: λ��������,����0
/************************************************************************/
byte GetDigit(DWORD dwValue, byte byDigit)
{
	char cTemp[30] = {0};
	_itoa_s(dwValue, cTemp, _countof(cTemp), 10);

	// ascii - 48 = ����
	UNINT nLen = strlen(cTemp);
	if ( nLen < byDigit + 1)
	{
		return 0;
	}

	byte byDigitValue = cTemp[nLen - 1 -  byDigit] - 48;
	return byDigitValue;
}

/***********�����㷨*****************************/

/************************************************************************/
/*	fun: ���ֲ���
/************************************************************************/
template<class T>
int BinarySearch(T* arr, DWORD dwCount, const T& key)
{
	DWORD dwLow = 0;
	DWORD dwHigh = dwCount - 1;
	
	DWORD dwMid = 0;
	int iPos = 0;
	for (;dwLow <= dwHigh;)
	{
		dwMid = (dwLow + dwHigh) / 2;
		if (key > arr[dwMid] )
		{
			dwLow = dwMid + 1;
		}
		else if(key < arr[dwMid])
		{
			dwHigh = dwMid - 1;
		}
		else
		{
			//�ҵ���
			return dwMid;
		}
		++iPos;
	}
	return -1;
}

/************************************************************************/
/*	fun:�ֿ����                                                            
/************************************************************************/
//BlockSearch()
//{
//	//ȷ��Ҫ�ֳɼ���
//}


/*-----��������---------------------------------------------------*/

/************************************************************************/
/*  fun: ��ȡ�����е���Сֵ                                        
    ret: ���ֵ��λ��    
/************************************************************************/
template<class T>
DWORD Min(T* arr, DWORD lCount)
{
	UNLONG dwMinIndex = 0;
	
	for (UNLONG i = 1;i<lCount;++i)
	{
		if (arr[i] < arr[dwMinIndex])
		{
			dwMinIndex = i;
		}
	}
	return dwMinIndex;
}

template<class T>
DWORD Min(T* arr, DWORD pos1, DWORD pos2)
{
	if (arr[pos1] <= arr[pos2])
	{
		return pos1;
	}
	return pos2;
}
/************************************************************************/
/*  fun: ��ȡ�����е����ֵ                                        
    ret: ���ֵ��λ��    
/************************************************************************/
template<class T>
DWORD Max(T* arr, DWORD lCount)
{
    UNLONG dwMaxIndex = 0;

    for (UNLONG i = 1;i<lCount;++i)
    {
        if (arr[i] > arr[dwMaxIndex])
        {
            dwMaxIndex = i;
        }
    }
    return dwMaxIndex;
}

/************************************************************************/
/*	fun:������3��ֵ�Ƚ�, �������ֵ������                                                                     
	ret:�������ֵ������ 
/************************************************************************/
template<class T>
DWORD MaxIn3(T* arr, DWORD pos1, DWORD pos2, DWORD pos3)
{
	UNLONG dwMaxIndex = 0;
	DWORD max1 = Max(arr, pos1, pos2);
	return Max(arr, max1, pos3);
}

//
/************************************************************************/
/*	fun:���ֵ,������Ԫ�صıȽ�                                                                     
	ret:�������ֵ������ 
/************************************************************************/
template<class T>
DWORD Max(T* arr, DWORD pos1, DWORD pos2)
{
	if (arr[pos1] >= arr[pos2])
	{
		return pos1;
	}
	return pos2;
}

template <class T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b= temp;
}

//������ֵ˳�򲻶�,�򽻻�λ��
template <class T>
void SwapIfMax(T* arr, DWORD pos1, DWORD pos2)
{
	if(pos2 == Max(arr, pos1, pos2))
	{
		Swap(arr[pos1], arr[pos2]);
	}
	
}