/* 2016-11-17 20121275 서정민 ex12_14.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BEGIN_LEARNING_RATE_A 0.5 // 전반부 초기 학습율 
#define BEGIN_LEARNING_RATE_B 0.2 // 후반부 초기 학습율
#define LEARNING_REDUCTION_RATIO 0.01 // 학습율 감소 비율
#define LEARNING_MIN_RATIO 0.01 // 학습율 최소 비율
#define NUMBER_OF_PATTERN 11 // 만들어지는 총 패턴(클러스터) 수 (BEGIN_LEARNING_RATE_A / LEARNING_REDUCTION_RATIO)
#define RANDNUMBER_A (2 + (rand() % 100 / 100.0f)) // 2.00 ~ 2.99 사이의 랜덤 넘버
#define RANDNUMBER_B (8 + (rand() % 1900 / 100.0f)) // 8.00 ~ 27.00 사이의 랜덤 넘버
#define RANDNUMBER_C (2 + (rand() % 100 / 100.0f)) // 2.00 ~ 2.99 사이의 랜덤 넘버

// 웨이트값 변동여부 식별을 위한 이넘 형식 선언
typedef enum { false, true } Bool;

// 트레이닝셋 저장을 위한 구조체 형식 선언
typedef struct
{
	float inputData; // 학습 데이터
	float desiredOutput; // 목표 출력 값
} TrainingSet;


int main()
{
	// V, W(전후반) 기본 연결강도 초기화
	float vWeight[NUMBER_OF_PATTERN] = { RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A };
	float wWeight[NUMBER_OF_PATTERN] = { RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B };

	// 현재 웨이트 표시
	printf("\n << WEIGHT RESULTS ! >> \n");
	printf("V-Weights : ");
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // 패턴별 탐색
	{
		printf("%1.2f, ", vWeight[index0]);
	}
	printf("\n");
	printf("W-Weights : ");
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // 패턴별 탐색
	{
		printf("%1.2f, ", wWeight[index0]);
	}
	printf("\n");

	// 트레이닝셋 초기화 (y = x^3)
	TrainingSet trainingSets[NUMBER_OF_PATTERN] = { 0 };
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0)
	{
		trainingSets[index0].inputData = RANDNUMBER_C;
		trainingSets[index0].desiredOutput = pow(trainingSets[index0].inputData, 3); // y = x^3

		printf("X : %1.2f → Y : %1.2f \n", trainingSets[index0].inputData, trainingSets[index0].desiredOutput);
	}

	// 전반부 학습 시작
	printf("\n << TRAINING MODE START ! >> \n");
	int epochCount = 0;
	for (float learnRatio = BEGIN_LEARNING_RATE_A; learnRatio >= LEARNING_MIN_RATIO; learnRatio -= LEARNING_REDUCTION_RATIO) // ratio는 학습 강도
	{
		printf("\n┌ ─ ─ V epoch : %2d / ratio : %1.2f ─ ─ ┐\n", ++epochCount, learnRatio);
		// Winner 뉴런 찾기 시작
		for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // 패턴별 탐색
		{
			float vMinOutput = 500.0; // 최소 유클리드 거리
			int vMinNum = -1; // Winner 뉴런 번호

			for (int index1 = 0; index1 < NUMBER_OF_PATTERN; ++index1) // 뉴런별 탐색
			{
				if (pow(trainingSets[index0].inputData - vWeight[index1], 2) < vMinOutput)
				{
					vMinOutput = pow(trainingSets[index0].inputData - vWeight[index1], 2); // 가장 짧은 유클리드 거리값 저장
					vMinNum = index1; // 가장 짧은 유클리드 거리를 가지는 뉴런의 번호 저장
				}
			}

			// 찾은 Winner 뉴런을 instar 학습
			float buffer = vWeight[vMinNum]; // 이전값 저장용
			vWeight[vMinNum] = vWeight[vMinNum] + (trainingSets[index0].inputData - vWeight[vMinNum]) * learnRatio; // 목표치와의 차이만큼 저장
			printf("< V-Weight : %d / Win : %d > %1.2f >> %1.2f \n", index0, vMinNum, buffer, vWeight[vMinNum]);
		}
		printf("\n");
	}

	// 후반부 학습 시작
	for (float learnRatio = BEGIN_LEARNING_RATE_B; learnRatio >= LEARNING_MIN_RATIO; learnRatio -= LEARNING_REDUCTION_RATIO) // ratio는 학습 강도
	{
		printf("\n┌ ─ ─ V & W epoch : %02d / ratio : %1.2f ─ ─ ┐\n", ++epochCount, learnRatio);
		// Winner 뉴런 찾기 시작
		for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // 패턴별 탐색
		{
			float vMinOutput = 500.0; // 최소 유클리드 거리
			int vMinNum = -1; // Winner 뉴런 번호

			for (int index1 = 0; index1 < NUMBER_OF_PATTERN; ++index1) // 뉴런별 탐색
			{
				if (pow(trainingSets[index0].inputData - vWeight[index1], 2) < vMinOutput)
				{
					vMinOutput = pow(trainingSets[index0].inputData - vWeight[index1], 2); // 가장 짧은 유클리드 거리값 저장
					vMinNum = index1; // 가장 짧은 유클리드 거리를 가지는 뉴런의 번호 저장
				}
			}

			// 찾은 Winner 뉴런을 instar 학습
			float vBuffer = vWeight[vMinNum]; // 이전값 저장용
			vWeight[vMinNum] = vWeight[vMinNum] + (trainingSets[index0].inputData - vWeight[vMinNum]) * LEARNING_MIN_RATIO; // 목표치와의 차이만큼 저장
			printf("< V-Weight : %02d / Win : %02d > %1.2f >> %1.2f \n", index0, vMinNum, vBuffer, vWeight[vMinNum]);

			// 찾은 Winner 뉴런을 outstar 학습
			float wBuffer = wWeight[vMinNum]; // 이전값 저장용
			wWeight[vMinNum] = wWeight[vMinNum] + (trainingSets[index0].desiredOutput - wWeight[vMinNum]) * learnRatio; // 목표치와의 차이만큼 저장
			printf("< W-Weight : %02d / Win : %02d > %1.2f >> %1.2f \n", index0, vMinNum, wBuffer, wWeight[vMinNum]);
		}
		printf("\n");
	}

	// 현재 웨이트 표시
	printf("\n << WEIGHT RESULTS ! >> \n");
	printf("V-Weights : ");
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // 패턴별 탐색
	{
		printf("%1.2f, ", vWeight[index0]);
	}
	printf("\n");
	printf("W-Weights : ");
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // 패턴별 탐색
	{
		printf("%1.2f, ", wWeight[index0]);
	}
	printf("\n");

	// 테스트 모드 시작
	printf("\n << START TEST MODE ! >> \n");
	float testInupt[4] = { 2.78, 2.05, 2.45, 2.95 };
	// Winner 뉴런 찾기 시작
	for (int index0 = 0; index0 < 4; ++index0) // 테스트 셋은 4개
	{
		float vMinOutput = 500.0; // 최소 유클리드 거리
		int vMinNum = -1; // Winner 뉴런 번호

		for (int index1 = 0; index1 < NUMBER_OF_PATTERN; ++index1) // 뉴런별 탐색
		{
			if (pow(testInupt[index0] - vWeight[index1], 2) < vMinOutput)
			{
				vMinOutput = pow(testInupt[index0] - vWeight[index1], 2); // 가장 짧은 유클리드 거리값 저장
				vMinNum = index1; // 가장 짧은 유클리드 거리를 가지는 뉴런의 번호 저장
			}
		}

		// 테스트 결과 출력
		printf("> X = %1.2f / Y = %1.2f (X^3 = %1.2f)", testInupt[index0], wWeight[vMinNum], pow(testInupt[index0], 3));
		printf("\n");
	}

	printf("\n\n");

	system("pause");
	return 0;
}