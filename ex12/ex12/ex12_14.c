/* 2016-11-17 20121275 ������ ex12_14.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BEGIN_LEARNING_RATE_A 0.5 // ���ݺ� �ʱ� �н��� 
#define BEGIN_LEARNING_RATE_B 0.2 // �Ĺݺ� �ʱ� �н���
#define LEARNING_REDUCTION_RATIO 0.01 // �н��� ���� ����
#define LEARNING_MIN_RATIO 0.01 // �н��� �ּ� ����
#define NUMBER_OF_PATTERN 11 // ��������� �� ����(Ŭ������) �� (BEGIN_LEARNING_RATE_A / LEARNING_REDUCTION_RATIO)
#define RANDNUMBER_A (2 + (rand() % 100 / 100.0f)) // 2.00 ~ 2.99 ������ ���� �ѹ�
#define RANDNUMBER_B (8 + (rand() % 1900 / 100.0f)) // 8.00 ~ 27.00 ������ ���� �ѹ�
#define RANDNUMBER_C (2 + (rand() % 100 / 100.0f)) // 2.00 ~ 2.99 ������ ���� �ѹ�

// ����Ʈ�� �������� �ĺ��� ���� �̳� ���� ����
typedef enum { false, true } Bool;

// Ʈ���̴׼� ������ ���� ����ü ���� ����
typedef struct
{
	float inputData; // �н� ������
	float desiredOutput; // ��ǥ ��� ��
} TrainingSet;


int main()
{
	// V, W(���Ĺ�) �⺻ ���ᰭ�� �ʱ�ȭ
	float vWeight[NUMBER_OF_PATTERN] = { RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A, RANDNUMBER_A };
	float wWeight[NUMBER_OF_PATTERN] = { RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B, RANDNUMBER_B };

	// ���� ����Ʈ ǥ��
	printf("\n << WEIGHT RESULTS ! >> \n");
	printf("V-Weights : ");
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // ���Ϻ� Ž��
	{
		printf("%1.2f, ", vWeight[index0]);
	}
	printf("\n");
	printf("W-Weights : ");
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // ���Ϻ� Ž��
	{
		printf("%1.2f, ", wWeight[index0]);
	}
	printf("\n");

	// Ʈ���̴׼� �ʱ�ȭ (y = x^3)
	TrainingSet trainingSets[NUMBER_OF_PATTERN] = { 0 };
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0)
	{
		trainingSets[index0].inputData = RANDNUMBER_C;
		trainingSets[index0].desiredOutput = pow(trainingSets[index0].inputData, 3); // y = x^3

		printf("X : %1.2f �� Y : %1.2f \n", trainingSets[index0].inputData, trainingSets[index0].desiredOutput);
	}

	// ���ݺ� �н� ����
	printf("\n << TRAINING MODE START ! >> \n");
	int epochCount = 0;
	for (float learnRatio = BEGIN_LEARNING_RATE_A; learnRatio >= LEARNING_MIN_RATIO; learnRatio -= LEARNING_REDUCTION_RATIO) // ratio�� �н� ����
	{
		printf("\n�� �� �� V epoch : %2d / ratio : %1.2f �� �� ��\n", ++epochCount, learnRatio);
		// Winner ���� ã�� ����
		for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // ���Ϻ� Ž��
		{
			float vMinOutput = 500.0; // �ּ� ��Ŭ���� �Ÿ�
			int vMinNum = -1; // Winner ���� ��ȣ

			for (int index1 = 0; index1 < NUMBER_OF_PATTERN; ++index1) // ������ Ž��
			{
				if (pow(trainingSets[index0].inputData - vWeight[index1], 2) < vMinOutput)
				{
					vMinOutput = pow(trainingSets[index0].inputData - vWeight[index1], 2); // ���� ª�� ��Ŭ���� �Ÿ��� ����
					vMinNum = index1; // ���� ª�� ��Ŭ���� �Ÿ��� ������ ������ ��ȣ ����
				}
			}

			// ã�� Winner ������ instar �н�
			float buffer = vWeight[vMinNum]; // ������ �����
			vWeight[vMinNum] = vWeight[vMinNum] + (trainingSets[index0].inputData - vWeight[vMinNum]) * learnRatio; // ��ǥġ���� ���̸�ŭ ����
			printf("< V-Weight : %d / Win : %d > %1.2f >> %1.2f \n", index0, vMinNum, buffer, vWeight[vMinNum]);
		}
		printf("\n");
	}

	// �Ĺݺ� �н� ����
	for (float learnRatio = BEGIN_LEARNING_RATE_B; learnRatio >= LEARNING_MIN_RATIO; learnRatio -= LEARNING_REDUCTION_RATIO) // ratio�� �н� ����
	{
		printf("\n�� �� �� V & W epoch : %02d / ratio : %1.2f �� �� ��\n", ++epochCount, learnRatio);
		// Winner ���� ã�� ����
		for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // ���Ϻ� Ž��
		{
			float vMinOutput = 500.0; // �ּ� ��Ŭ���� �Ÿ�
			int vMinNum = -1; // Winner ���� ��ȣ

			for (int index1 = 0; index1 < NUMBER_OF_PATTERN; ++index1) // ������ Ž��
			{
				if (pow(trainingSets[index0].inputData - vWeight[index1], 2) < vMinOutput)
				{
					vMinOutput = pow(trainingSets[index0].inputData - vWeight[index1], 2); // ���� ª�� ��Ŭ���� �Ÿ��� ����
					vMinNum = index1; // ���� ª�� ��Ŭ���� �Ÿ��� ������ ������ ��ȣ ����
				}
			}

			// ã�� Winner ������ instar �н�
			float vBuffer = vWeight[vMinNum]; // ������ �����
			vWeight[vMinNum] = vWeight[vMinNum] + (trainingSets[index0].inputData - vWeight[vMinNum]) * LEARNING_MIN_RATIO; // ��ǥġ���� ���̸�ŭ ����
			printf("< V-Weight : %02d / Win : %02d > %1.2f >> %1.2f \n", index0, vMinNum, vBuffer, vWeight[vMinNum]);

			// ã�� Winner ������ outstar �н�
			float wBuffer = wWeight[vMinNum]; // ������ �����
			wWeight[vMinNum] = wWeight[vMinNum] + (trainingSets[index0].desiredOutput - wWeight[vMinNum]) * learnRatio; // ��ǥġ���� ���̸�ŭ ����
			printf("< W-Weight : %02d / Win : %02d > %1.2f >> %1.2f \n", index0, vMinNum, wBuffer, wWeight[vMinNum]);
		}
		printf("\n");
	}

	// ���� ����Ʈ ǥ��
	printf("\n << WEIGHT RESULTS ! >> \n");
	printf("V-Weights : ");
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // ���Ϻ� Ž��
	{
		printf("%1.2f, ", vWeight[index0]);
	}
	printf("\n");
	printf("W-Weights : ");
	for (int index0 = 0; index0 < NUMBER_OF_PATTERN; ++index0) // ���Ϻ� Ž��
	{
		printf("%1.2f, ", wWeight[index0]);
	}
	printf("\n");

	// �׽�Ʈ ��� ����
	printf("\n << START TEST MODE ! >> \n");
	float testInupt[4] = { 2.78, 2.05, 2.45, 2.95 };
	// Winner ���� ã�� ����
	for (int index0 = 0; index0 < 4; ++index0) // �׽�Ʈ ���� 4��
	{
		float vMinOutput = 500.0; // �ּ� ��Ŭ���� �Ÿ�
		int vMinNum = -1; // Winner ���� ��ȣ

		for (int index1 = 0; index1 < NUMBER_OF_PATTERN; ++index1) // ������ Ž��
		{
			if (pow(testInupt[index0] - vWeight[index1], 2) < vMinOutput)
			{
				vMinOutput = pow(testInupt[index0] - vWeight[index1], 2); // ���� ª�� ��Ŭ���� �Ÿ��� ����
				vMinNum = index1; // ���� ª�� ��Ŭ���� �Ÿ��� ������ ������ ��ȣ ����
			}
		}

		// �׽�Ʈ ��� ���
		printf("> X = %1.2f / Y = %1.2f (X^3 = %1.2f)", testInupt[index0], wWeight[vMinNum], pow(testInupt[index0], 3));
		printf("\n");
	}

	printf("\n\n");

	system("pause");
	return 0;
}