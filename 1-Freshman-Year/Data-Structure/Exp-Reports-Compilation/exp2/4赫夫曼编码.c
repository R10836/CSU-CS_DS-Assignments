#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 100 // ����ַ�����С

// �շ������ڵ�
typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
} HuffmanNode;

// �շ�����
typedef struct HuffmanTree {
    HuffmanNode* root;
} HuffmanTree;

// �ַ�����
typedef struct CharacterCode {
    char character;
    char code[MAX_CHARACTERS];
} CharacterCode;

// ��ʼ���շ�����
void initializeHuffmanTree(HuffmanTree* tree, char* characters, int* frequencies, int size) {
    // TODO: �����ַ�����Ƶ�ʽ����շ�����
    // ����ʹ�öѻ����ȶ�����ʵ�ֺշ������Ĺ���
}

// ���ݺշ����������Ľ��б���
void encodeText(HuffmanTree* tree, char* text, CharacterCode* codes, int size, char* encodedText) {
    // TODO: ���ݺշ����������Ľ��б���
}

// ���ݺշ�������������
void decodeText(HuffmanTree* tree, char* encodedText, char* decodedText) {
    // TODO: ���ݺշ������Ա������ı���������
}

// ��ӡ�����ļ�
void printCodeFile(char* encodedText) {
    // TODO: �����ո�ʽ��ʾ�����ļ���ÿ��50���ַ�
}

// ��ӡ�շ�����
void printHuffmanTree(HuffmanNode* root, int level) {
    // TODO: ��ֱ�۷�ʽ��ʾ�շ��������ַ���ʽ
}

int main() {
    char characters[MAX_CHARACTERS]; // �ַ���
    int frequencies[MAX_CHARACTERS]; // Ƶ��
    int size; // �ַ�����С
    HuffmanTree tree;
    CharacterCode codes[MAX_CHARACTERS];

    // �˵�ѭ��
    char choice;
    do {
        printf("\n�˵�\n");
        printf("I. ��ʼ��\n");
        printf("E. ����\n");
        printf("D. ����\n");
        printf("P. ��ӡ�����ļ�\n");
        printf("T. ��ӡ�շ�����\n");
        printf("Q. �˳�\n");
        printf("��ѡ���ܷ���");
        scanf(" %c", &choice);

        switch (choice) {
            case 'I': {
                // ��ʼ���շ�����
                printf("�������ַ�����С��");
                scanf("%d", &size);

                printf("�������ַ�����Ƶ�ʣ��ÿո�ָ�����\n");
                for (int i = 0; i < size; i++) {
                    scanf(" %c %d", &characters[i], &frequencies[i]);
                }

                initializeHuffmanTree(&tree, characters, frequencies, size);
                printf("�շ������ѳ�ʼ����\n");
                break;
            }
            case 'E': {
                // ����
                char text[100];
                printf("������Ҫ��������ģ�");
                scanf(" %[^\n]", text);

                char encodedText[1000];
                encodeText(&tree, text, codes, size, encodedText);
                printf("�������ı���\n%s\n", encodedText);
                break;
            }
            case 'D': {
                // ����
                char encodedText[1000];
                printf("������Ҫ����ı����ı���");
                scanf(" %[^\n]", encodedText);

                char decodedText[100];
                decodeText(&tree, encodedText, decodedText);
                printf("�������ı���\n%s\n", decodedText);
                break;
            }
            case 'P': {
                // ��ӡ�����ļ�
                char encodedText[1000];
                printf("������Ҫ��ӡ�ı����ı���");
                scanf(" %[^\n]", encodedText);

                printCodeFile(encodedText);
                printf("�����ļ��Ѵ�ӡ��\n");
                break;
            }
            case 'T': {
                // ��ӡ�շ�����
                printHuffmanTree(tree.root, 0);
                printf("�շ������Ѵ�ӡ��\n");
                break;
            }
            case 'Q':
                printf("�������˳���\n");
                break;
            default:
                printf("��Ч��ѡ�����������롣\n");
        }
    } while (choice != 'Q');

    return 0;
}
