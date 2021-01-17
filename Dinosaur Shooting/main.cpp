#include "DxLib.h"
#include <time.h>

//########## �}�N����` ##########
#define GAME_WIDTH			800	//��ʂ̉��̑傫��
#define GAME_HEIGHT			600	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"GAME TITLE"	//�E�B���h�E�̃^�C�g��



#define GAME_FPS			60	//FPS�̐��l	

#define PATH_MAX            100

//---------------------------------------------------------------------------------------------------------�摜�ndefine��--------------------//

#define IMAGE_PLAY_BK_PATH			TEXT(".\\IMAGE\\PLAY_BK.png")		//�^�C�g���w�i�̉摜
#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\TITLE_BK.png")		//�^�C�g���w�i�̉摜
#define IMAGE_PLAYER_PATH		    TEXT(".\\IMAGE\\PLAYER.png")	//�v���C���[�̉摜
#define IMAGE_DINO1_PATH            TEXT(".\\IMAGE\\DINO1.png")


#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")



typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}IMAGE;	//�摜�\����

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE	129		//0x0000�`0x0080�܂�

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//�Q�[���̃V�[��

enum CHARA_SPEED {
	CHARA_SPEED_RELOAD = 1,
	CHARA_SPEED_REX = 2,
	CHARA_SPEED_USE = 5
};	//�L�����N�^�[�̃X�s�[�h

enum DINO_SPEED {
	DINO_SPEED_WARK = 1,
	DINO_SPEED_NORMAL = 4,
	DINO_SPPED_ANGRY = 5
};

typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE�\����
	int speed;					//����
	int CenterX;				//���SX
	int CenterY;				//���SY

	int JumpNowY;
	int JumpRakkaY;

	BOOL CanJump;

}CHARA;	//�L�����N�^�[�\����

typedef struct STRUCT_DINO
{
	IMAGE image;				//IMAGE�\����
	int speed;					//����
	int CenterX;				//���SX
	int CenterY;				//���SY

	int JumpNowY;
	int JumpRakkaY;

	BOOL CanJump;
	BOOL CanMove;
	BOOL DinoMove;

}DINO;	//�G�L�����\����

//int�^��POINT�\����
typedef struct STRUCT_I_POINT
{
	int x = -1;	//���W��������
	int y = -1;	//���W��������
}iPOINT;

//�}�E�X�\����
typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInput�̒l������
	int WheelValue = 0;	//�}�E�X�z�C�[���̉�]��(���̓v���X�l / ��O�̓}�C�i�X�l)
	iPOINT Point;		//�}�E�X�̍��W������
	iPOINT OldPoint;	//�}�E�X�̍��W(���O)������
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//�}�E�X�̃{�^������(���O)������
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//�}�E�X�̃{�^�����͂�����
}MOUSE;

//########## �O���[�o���ϐ� ##########
//FPS�֘A
int StartTimeFps;				//����J�n����
int CountFps;					//�J�E���^
float CalcFps;					//�v�Z����
int SampleNumFps = GAME_FPS;	//���ς����T���v����

//�L�[�{�[�h�̓��͂��擾
char AllKeyState[256] = { '\0' };			//���ׂẴL�[�̏�Ԃ�����
char OldAllKeyState[256] = { '\0' };	//���ׂẴL�[�̏��(���O)������

//�}�E�X�̍��W���擾
MOUSE mouse;


int GameScene;		//�Q�[���V�[�����Ǘ�

IMAGE ImageBack;		//�Q�[���̔w�i
IMAGE ImageTitleBK;		//�^�C�g���w�i�̉��
CHARA player;			//�Q�[���̃L����
DINO dino;				//�Q�[���̓G�L����


//########## �v���g�^�C�v�錾 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS�l���v���A�X�V����
VOID MY_FPS_DRAW(VOID);				//FPS�l��`�悷��
VOID MY_FPS_WAIT(VOID);				//FPS�l���v�����A�҂�

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int);				//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_UP(int);				//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEYDOWN_KEEP(int, int);		//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����

VOID MY_MOUSE_UPDATE(VOID);			//�}�E�X�̓��͏����X�V����
BOOL MY_MOUSE_DOWN(int);			//�{�^���������Ă��邩�A�}�E�X�R�[�h�Ŕ��f����
BOOL MY_MOUSE_UP(int);				//�{�^���������グ�����A�}�E�X�R�[�h�Ŕ��f����
BOOL MY_MOUSEDOWN_KEEP(int, int);	//�{�^�������������Ă��邩�A�}�E�X�R�[�h�Ŕ��f����	

VOID MY_START(VOID);		//�X�^�[�g���
VOID MY_START_PROC(VOID);	//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);	//�X�^�[�g��ʂ̕`��

VOID MY_PLAY(VOID);			//�v���C���
VOID MY_PLAY_PROC(VOID);	//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);	//�v���C��ʂ̕`��

VOID MY_END(VOID);			//�G���h���
VOID MY_END_PROC(VOID);		//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);		//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);		//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);		//�摜���܂Ƃ߂č폜����֐�

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	if (MY_LOAD_IMAGE() == FALSE) { return -1; } //�摜��ǂݍ���

	SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��	

    player.CanJump = TRUE;
	dino.CanJump = TRUE;
	dino.CanMove = TRUE;

	int DrawX = 0;	//�\���ʒuX
	int DrawY = 0;	//�\���ʒuY

	iPOINT InputFirst = { 0,0 };	//�n�_
	iPOINT InputEnd = { 0,0 };		//�I�_
	BOOL IsMouseDownLeft = FALSE;	//�}�E�X�̍��{�^������������

	GameScene = GAME_SCENE_START;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��擾

		MY_MOUSE_UPDATE();						//�}�E�X�̏�Ԃ��擾

		MY_FPS_UPDATE();	//FPS�̏���[�X�V]


		if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE) { mouse.Point.x++; }
		if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE) { mouse.Point.x--; }

		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//�X�^�[�g���
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//�v���C���
			break;
		case GAME_SCENE_END:
			MY_END();	//�G���h���
			break;
		}

		MY_FPS_DRAW();		//FPS�̏���[�`��]

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		MY_FPS_WAIT();		//FPS�̏���[�҂�]
	}

	MY_DELETE_IMAGE();	

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	return 0;
}

//########## FPS�l���v���A�X�V����֐� ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1�t���[���ڂȂ玞�����L��
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60�t���[���ڂȂ畽�ς��v�Z
	{
		int now = GetNowCount();
		//���݂̎��Ԃ���A0�t���[���ڂ̎��Ԃ������AFPS�̐��l�Ŋ��遁1FPS�ӂ�̕��ώ��Ԃ��v�Z�����
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS�l��`�悷��֐� ##########
VOID MY_FPS_DRAW(VOID)
{
	//�������`��
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS�l���v�����A�҂֐� ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//������������
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//�҂ׂ�����

	if (waitTime > 0)		//�w���FPS�l���������ꍇ
	{
		WaitTimer(waitTime);	//�҂�
	}
	return;
}

//########## �L�[�̓��͏�Ԃ��X�V����֐� ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	//�Q�l�Fhttps://dxlib.xsrv.jp/function/dxfunc_input.html

	char TempKey[256];	//�ꎞ�I�ɁA���݂̃L�[�̓��͏�Ԃ��i�[����

	//���O�̃L�[���͂��Ƃ��Ă���
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//������Ă���L�[�̃L�[�R�[�h�������Ă���Ƃ�
		{
			AllKeyState[i]++;	//������Ă���
		}
		else
		{
			AllKeyState[i] = 0;	//������Ă��Ȃ�
		}
	}
	return;
}

//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//�L�[�R�[�h�̃L�[�������Ă��鎞
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//�L�[�������Ă���
	}
	else
	{
		return FALSE;	//�L�[�������Ă��Ȃ�
	}
}

//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//���O�͉����Ă���
		&& AllKeyState[KEY_INPUT_] == 0)	//���͉����Ă��Ȃ��Ƃ�
	{
		return TRUE;	//�L�[�������グ�Ă���
	}
	else
	{
		return FALSE;	//�L�[�������グ�Ă��Ȃ�
	}
}

//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
//���@���Fint�F�L�[�����������鎞��
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//���������鎞��=�b���~FPS�l
	//��j60FPS�̃Q�[���ŁA1�b�ԉ���������Ȃ�A1�b�~60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//���������Ă���
	}
	else
	{
		return FALSE;	//���������Ă��Ȃ�
	}
}

//�}�E�X�̓��͏����X�V����
VOID MY_MOUSE_UPDATE(VOID)
{

	//�}�E�X�̈ȑO�̃{�^�����͂��擾
	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	//�}�E�X�̉����Ă���{�^�����擾
	mouse.InputValue = GetMouseInput();

	//���{�^���������Ă��邩�`�F�b�N(TRUE��0�ȊO�Ȃ̂ŁA2��4��TRUE)
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }		//�����Ă���
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }		//�����Ă��Ȃ�

	//���{�^���������Ă��邩�`�F�b�N(TRUE��0�ȊO�Ȃ̂ŁA2��4��TRUE)
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }	//�����Ă���
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }	//�����Ă��Ȃ�

	//�E�{�^���������Ă��邩�`�F�b�N(TRUE��0�ȊO�Ȃ̂ŁA2��4��TRUE)
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }		//�����Ă���
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }	//�����Ă��Ȃ�

	//�z�C�[���̉�]�ʂ��擾
	mouse.WheelValue = GetMouseWheelRotVol();

	return;
}

//�{�^���������Ă��邩�A�}�E�X�[�R�[�h�Ŕ��f����
//���@���Fint�F�}�E�X�R�[�h�FMOUSE_INPUT_???
BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	//�}�E�X�R�[�h�̃{�^���������Ă��鎞
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;	//�{�^���������Ă���
	}
	else
	{
		return FALSE;	//�{�^���������Ă��Ȃ�
	}
}

//�{�^���������グ�����A�}�E�X�R�[�h���f����
//���@���Fint�F�}�E�X�R�[�h�FMOUSE_INPUT_???
BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1	//���O�͉����Ă���
		&& mouse.Button[MOUSE_INPUT_] == 0)	//���͉����Ă��Ȃ��Ƃ�
	{
		return TRUE;	//�{�^���������グ�Ă���
	}
	else
	{
		return FALSE;	//�{�^���������グ�Ă��Ȃ�
	}
}

//�{�^�������������Ă��邩�A�}�E�X�R�[�h���f����
//���@���Fint�F�}�E�X�R�[�h�FMOUSE_INPUT_???
//���@���Fint�F�{�^�������������鎞��
BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	//���������鎞��=�b���~FPS�l
	//��j60FPS�̃Q�[���ŁA1�b�ԉ���������Ȃ�A1�b�~60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;	//���������Ă���
	}
	else
	{
		return FALSE;	//���������Ă��Ȃ�
	}
}

//�t�H���g��ǂݍ��ފ֐�
//���@���Fconst char *�F�ǂݍ��ރt�H���g�̖��O
//���@���Fint�@�F�t�H���g�̑傫��
//���@���Fint�@�F�t�H���g�̑���
//���@���Fint�@�F�t�H���g�̃^�C�v
//�߂�l�F�Ȃ����ύX���߂�l�FBOOL�F�G���[���FFALSE

//���������� �v���O�����ǉ��������� ����������������������������������������

//�X�^�[�g���
VOID MY_START(VOID)
{
	MY_START_PROC();	//�X�^�[�g��ʂ̏���
	MY_START_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�X�^�[�g��ʂ̏���
VOID MY_START_PROC(VOID)
{
	//�G���^�[�L�[����������A�v���C�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_PLAY;
	}

	return;
}

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageBack.x, ImageBack.y, ImageTitleBK.handle, TRUE);

	DrawString(0, 0, "�X�^�[�g���(�G���^�[�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//�v���C��ʂ̏���
	MY_PLAY_DRAW();	//�v���C��ʂ̕`��

	return;
}

//�v���C��ʂ̏���
VOID MY_PLAY_PROC(VOID)
{
	//�X�y�[�X�L�[����������A�G���h�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_I) == TRUE)
	{
		GameScene = GAME_SCENE_END;
	}

	if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE) { player.CenterX = player.CenterX - CHARA_SPEED_USE; }
	if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE) { player.CenterX = player.CenterX + CHARA_SPEED_USE; }

	player.CenterY += 10;
	dino.CenterY += 10;

	if (dino.CanMove == TRUE)
	{
		srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
		dino.DinoMove = rand() % 3 + 1; // 1�`3�̗�������
		dino.CanMove = false;
	}

	//rand�֐��T���v���e�L�X�g
	//for (int i = 0; i < 3; i++) {
	//	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	//	printf("%d��ڂ̗�������: ", i + 1);

	//	// 1����10�܂ł̗����𔭐�
	//	for (int j = 0; j < 3; j++) {
	//		printf("%d, ", rand() % 10 + 1);
	//	}
	//	sleep(1); // time�֐��Ŏ擾���鎞����ς��邽�߂�1�b�ҋ@
	//	printf("\n");
	//}
	//

	if (dino.DinoMove == 1)
	{
		dino.CenterX -=10;

		if (dino.CenterX <= 0 + dino.image.width)
		{
			dino.CanMove = TRUE;
		}
	}

	if (dino.DinoMove == 2)
	{
		dino.CenterX += 10;

		if (dino.CenterX >= GAME_WIDTH - dino.image.width)
		{
			dino.CanMove = TRUE;
		}
	}

	if (dino.DinoMove == 3)
	{
		dino.CanMove = TRUE;
	}

	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE && player.CanJump == TRUE)
	{		
		player.CanJump == FALSE;

		while (TRUE)
		{
			int JumpTop = player.CenterY - 20;
			player.CenterY = player.CenterY--;

			if (player.CenterY = JumpTop)
			{
				player.CanJump == TRUE;
				break;
			}
		}
	}
	//if (MY_KEY_UP(KEY_INPUT_SPACE) == TRUE)
	//{
	//	for (int i = 0; i < 10; i++)
	//	{
	//		player.CenterY++;
	//	}
	//}

	//�v���C���[�̈ʒu�ɒu��������
	player.image.x = player.CenterX - player.image.width / 2;
	player.image.y = player.CenterY - player.image.height / 2;

	dino.image.x = dino.CenterX - dino.image.width / 2;
	dino.image.y = dino.CenterY - dino.image.height / 2;

	//��ʊO�Ƀv���C���[���s���Ȃ��悤�ɂ���
	if (player.CenterX - player.image.width / 2 < 0) { player.CenterX = 0 + player.image.width / 2; }
	if (player.CenterX + player.image.width / 2 > GAME_WIDTH) { player.CenterX = GAME_WIDTH - player.image.width / 2; }
	if (player.CenterY - player.image.height / 2 < 0) { player.CenterY = 0 + player.image.height / 2; }
	if (player.CenterY + player.image.height / 2 > GAME_HEIGHT) { player.CenterY = GAME_HEIGHT - player.image.height / 2; }

	if (dino.CenterX - dino.image.width / 2 < 0) { dino.CenterX = 0 + dino.image.width / 2; }
	if (dino.CenterX + dino.image.width / 2 > GAME_WIDTH) { dino.CenterX = GAME_WIDTH - dino.image.width / 2; }
	if (dino.CenterY - dino.image.height / 2 < 0) { dino.CenterY = 0 + dino.image.height / 2; }
	if (dino.CenterY + dino.image.height / 2 > GAME_HEIGHT) { dino.CenterY = GAME_HEIGHT - dino.image.height / 2; }
	
	//if (dino.CenterX < 0) { dino.CenterX = 0; }
	//if (dino.CenterX + dino.image.width > GAME_WIDTH) { dino.CenterX = GAME_WIDTH - dino.image.width; }
	//if (dino.CenterY < 0) { dino.CenterY = 0; }
	//if (dino.CenterY + dino.image.height > GAME_HEIGHT) { dino.CenterY = GAME_HEIGHT - dino.image.height; }

	////��ʊO�Ƀv���C���[���s���Ȃ��悤�ɂ���
	//if (player.image.x < 0) { player.image.x = 0; }
	//if (player.image.x + player.image.width > GAME_WIDTH) { player.image.x = GAME_WIDTH - player.image.width; }
	//if (player.image.y < 0) { player.image.y = 0; }
	//if (player.image.y + player.image.height > GAME_HEIGHT) { player.image.y = GAME_HEIGHT - player.image.height; }

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);

	//DrawExtendGraph(
	//	player.image.x, player.image.y,														//�R�R����
	//	player.image.x + player.image.width * 2, player.image.y + player.image.height * 2,	//�R�R�܂ň����L�΂�
	//	player.image.handle, TRUE);

	DrawGraph(
		player.image.x , player.image.y , player.image.handle , TRUE
	);

	DrawBox(player.image.x, player.image.y, player.image.x + player.image.width, player.image.y + player.image.height, GetColor(255, 255, 255), FALSE);

	//DrawExtendGraph(
	//	dino.image.x, dino.image.y,														//�R�R����
	//	dino.image.x + dino.image.width * 2, dino.image.y + dino.image.height * 2,	//�R�R�܂ň����L�΂�
	//	dino.image.handle, TRUE);

	DrawGraph(
		dino.image.x, dino.image.y, dino.image.handle, TRUE
	);

	DrawBox(dino.image.x, dino.image.y, dino.image.x + dino.image.width, dino.image.y + dino.image.height, GetColor(255, 255, 255), FALSE);

	DrawString(0, 0, "�v���C���(I�L�[�������ĉ�����)", GetColor(255, 255, 255));

	return;
}

//�G���h���
VOID MY_END(VOID)
{
	MY_END_PROC();	//�G���h��ʂ̏���
	MY_END_DRAW();	//�G���h��ʂ̕`��
	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	//�G�X�P�[�v�L�[����������A�X�^�[�g�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	//�̎l�p��`��
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

	DrawString(0, 0, "�G���h���(�G�X�P�[�v�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

//�摜���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_IMAGE(VOID)
{
	//�w�i�摜
	strcpy_s(ImageBack.path, IMAGE_PLAY_BK_PATH);		//�p�X�̐ݒ�
	ImageBack.handle = LoadGraph(ImageBack.path);	//�ǂݍ���
	if (ImageBack.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);			//�p�X�̐ݒ�
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);			//�ǂݍ���
	if (ImageTitleBK.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(ImageBack.handle, &ImageBack.width, &ImageBack.height);	//�摜�̕��ƍ������擾
	ImageBack.x = GAME_WIDTH / 2 - ImageBack.width / 2;		//���E��������
	ImageBack.y = GAME_HEIGHT / 2 - ImageBack.height / 2;	//�㉺��������

	//�v���C���[�̉摜
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//�p�X�̐ݒ�
	player.image.handle = LoadGraph(player.image.path);	//�ǂݍ���
	if (player.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//�摜�̕��ƍ������擾
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//���E��������
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//�㉺��������
	player.CenterX = player.image.x + player.image.width / 2;		//�摜�̉��̒��S��T��
	player.CenterY = player.image.y + player.image.height / 2;		//�摜�̏c�̒��S��T��
	player.speed = CHARA_SPEED_USE;




	strcpy_s(dino.image.path, IMAGE_DINO1_PATH);		//�p�X�̐ݒ�
	dino.image.handle = LoadGraph(dino.image.path);	//�ǂݍ���
	if (dino.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_DINO1_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(dino.image.handle, &dino.image.width, &dino.image.height);	//�摜�̕��ƍ������擾
	dino.image.x = GAME_WIDTH / 2 - dino.image.width / 2;		//���E��������
	dino.image.y = GAME_HEIGHT / 2 - dino.image.height / 2;		//�㉺��������
	dino.CenterX = dino.image.x + dino.image.width / 2;		//�摜�̉��̒��S��T��
	dino.CenterY = dino.image.y + dino.image.height / 2;		//�摜�̏c�̒��S��T��
	dino.speed = DINO_SPEED_NORMAL;




//	//�G�L�����̉摜
//	strcpy_s(dino.image.path, IMAGE_DINO1_PATH);		//�p�X�̐ݒ�
//	dino.image.handle = LoadGraph(dino.image.path);	//�ǂݍ���
//	if (dino.image.handle == -1)
//	{
//		//�G���[���b�Z�[�W�\��
//		MessageBox(GetMainWindowHandle(), IMAGE_DINO1_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(dino.image.handle, &dino.image.width, &dino.image.height);	//�摜�̕��ƍ������擾
//	dino.image.x = GAME_WIDTH / 2 - dino.image.width / 2;		//���E��������
//	dino.image.y = GAME_HEIGHT / 2 - dino.image.height / 2;		//�㉺��������
//	dino.CenterX = dino.image.x + dino.image.width / 2;		//�摜�̉��̒��S��T��
//	dino.CenterY = dino.image.y + dino.image.height / 2;		//�摜�̏c�̒��S��T��
//	dino.speed = DINO_SPEED_NORMAL;

	return TRUE;
}

//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageBack.handle);          //�v���C��ʍ폜
	DeleteGraph(ImageTitleBK.handle);       //�^�C�g����ʍ폜
//	DeleteGraph(player.image.handle);

	return;
}

