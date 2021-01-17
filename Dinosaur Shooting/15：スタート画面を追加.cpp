/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�X�^�[�g��ʂ�ǉ�

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "resource.h"

//########## �}�N����` ##########
#define GAME_WIDTH			800	//��ʂ̉��̑傫��
#define GAME_HEIGHT			600	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"GAME TITLE"	//�E�B���h�E�̃^�C�g��

#define GAME_FPS			60	//FPS�̐��l	

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE	129		//0x0000�`0x0080�܂�

//�p�X�̒���
#define PATH_MAX			255	//255�����܂�
#define NAME_MAX			255	//255�����܂�

//�t�H���g
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//�t�H���g�̏ꏊ
#define FONT_TANU_NAME			TEXT("���ʂ������}�W�b�N")			//�t�H���g�̖��O

//�G���[���b�Z�[�W
#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

//�G���[���b�Z�[�W
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

//�摜�̃p�X
#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\space1.png")	//�w�i�̉摜
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\player1.png")	//�v���C���[�̉摜

//���������� �v���O�����ǉ��������� ����������������������������������������

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\titleBK.png")		//�^�C�g���w�i�̉摜
#define IMAGE_TITLE_ROGO_PATH		TEXT(".\\IMAGE\\title_rogo.png")	//�^�C�g�����S�̉摜
#define IMAGE_TITLE_ROGO_ROTA		0.005		//�g�嗦
#define IMAGE_TITLE_ROGO_ROTA_MAX	1.0			//�g�嗦MAX
#define IMAGE_TITLE_ROGO_X_SPEED	1			//X�ړ����x
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\title_start.png")	//�^�C�g���X�^�[�g�̉摜
#define IMAGE_TITLE_START_CNT		1			//�_�ŃJ�E���^
#define IMAGE_TITLE_START_CNT_MAX	30			//�_�ŃJ�E���^MAX

//���������� �v���O�����ǉ������܂� ����������������������������������������

#define IMAGE_BACK_REV_PATH		TEXT(".\\IMAGE\\space2.png")	//�w�i�̉摜
#define IMAGE_BACK_NUM			4								//�w�i�̉摜�̐�

//�e�̐ݒ�
#define TAMA_CHANGE_MAX		 5	//5�t���[���ڂŒe�̉摜��ς���
#define TAMA_MAX			16	//�ő�16���܂�

#define TAMA_RED_PATH			TEXT(".\\IMAGE\\TAMA\\red.png")		//�Ԓe�̉摜
#define TAMA_GREEN_PATH			TEXT(".\\IMAGE\\TAMA\\green.png")	//�e�̉摜
#define TAMA_BLUE_PATH			TEXT(".\\IMAGE\\TAMA\\blue.png")	//�Βe�̉摜
#define TAMA_YELLOW_PATH		TEXT(".\\IMAGE\\TAMA\\yellow.png")	//���e�̉摜

#define TAMA_DIV_WIDTH		16	//�摜�𕪊����镝�T�C�Y
#define TAMA_DIV_HEIGHT		16	//�摜�𕪊����鍂���T�C�Y

#define TAMA_DIV_TATE		3	//�摜���c�ɕ������鐔
#define TAMA_DIV_YOKO		1	//�摜�����ɕ������鐔

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO	//�摜�𕪊����鑍��

//�G���[���b�Z�[�W
#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

//���y�̃p�X
#define MUSIC_BGM_PATH			TEXT(".\\MUSIC\\Mystery_of_the_Universe.mp3")	//BGM
#define MUSIC_PLAYER_SHOT_PATH	TEXT(".\\MUSIC\\�V���b�g��.mp3")				//�V���b�g��

#define GAME_MAP_TATE_MAX	9	//�}�b�v�̏c�̐�
#define GAME_MAP_YOKO_MAX	13	//�}�b�v�̉��̐�
#define GAME_MAP_KIND_MAX	2	//�}�b�v�̎�ނ̐�

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map.png")		//�}�b�v�̉摜

#define MAP_DIV_WIDTH		64	//�摜�𕪊����镝�T�C�Y
#define MAP_DIV_HEIGHT		64	//�摜�𕪊����鍂���T�C�Y
#define MAP_DIV_TATE		10	//�摜���c�ɕ������鐔
#define MAP_DIV_YOKO		4	//�摜�����ɕ������鐔
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//�摜�𕪊����鑍��

//�G���[���b�Z�[�W
#define START_ERR_TITLE		TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION	TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")

//�I���_�C�A���O�p
#define MOUSE_R_CLICK_TITLE		TEXT("�Q�[�����f")
#define MOUSE_R_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")

enum GAME_MAP_KIND
{
	n = -1,	//(NONE)����
	k = 0,	//��
	t = 9,	//�ʘH
	s = 5,	//�X�^�[�g
	g = 3	//�S�[��
};	//�}�b�v�̎��

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//�Q�[���̃V�[��

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//�L�����N�^�[�̃X�s�[�h

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};	//�L�����N�^�[�̃����[�h

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

//�t�H���g�\����
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];		//�p�X
	char name[NAME_MAX];		//�t�H���g��
	int handle;					//�n���h��
	int size;					//�傫��
	int bold;					//����
	int type;					//�^�C�v
	//���^�C�v�́Ahttps://dxlib.xsrv.jp/function/dxfunc_graph2.html#R17N10�@���Q��

}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}IMAGE;	//�摜�\����

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
}MUSIC;	//���y�\����

typedef struct STRUCT_TAMA
{
	char path[PATH_MAX];				//�p�X
	int handle[TAMA_DIV_NUM];			//���������̒e�̉摜�n���h�����擾
	int x;								//X�ʒu
	int y;								//Y�ʒu
	int width;							//��
	int height;							//����
	BOOL IsDraw;						//�e��\���ł��邩
	int nowImageKind;					//�e�̌��݂̉摜
	int changeImageCnt;					//�摜��ς��邽�߂̃J�E���g
	int changeImageCntMAX;				//�摜��ς��邽�߂̃J�E���g(MAX)
	int speed;							//�X�s�[�h
}TAMA;	//�e�̍\����

typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE�\����
	int speed;					//����
	int CenterX;				//���SX
	int CenterY;				//���SY

	MUSIC musicShot;			//�v���C���[�̔��ˉ�

	BOOL CanShot;				//�V���b�g�ł��邩
	int ShotReLoadCnt;			//�V���b�g�����[�h����
	int ShotReLoadCntMAX;		//�V���b�g�����[�h����(MAX)

	TAMA tama[TAMA_MAX];		//�V���b�g����e

	RECT coll;					//�����蔻��
	iPOINT collBeforePt;		//������O�̍��W

}CHARA;	//�L�����N�^�[�\����

typedef struct STRUCT_IMAGE_BACK
{
	IMAGE image;		//IMAGE�\����
	BOOL IsDraw;		//�e��\���ł��邩
}IMAGE_BACK;	//�w�i�摜�̍\����

//���������� �v���O�����ǉ��������� ����������������������������������������

typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;		//IMAGE�\����
	double angle;		//��]��
	double angleMAX;	//��]��MAX
	double rate;		//�g�嗦
	double rateMAX;		//�g�嗦MAX

}IMAGE_ROTA;	//��]�g�傷��摜�̍\����

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;		//IMAGE�\����
	int Cnt;			//�_�ŃJ�E���^
	int CntMAX;			//�_�ł��鎞��MAX
	BOOL IsDraw;		//�`��ł��邩�H

}IMAGE_BLINK;	//�_�ł���摜�̍\����

//���������� �v���O�����ǉ������܂� ����������������������������������������

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];				//�p�X
	int handle[MAP_DIV_NUM];			//���������̒e�̉摜�n���h�����擾
	int kind[MAP_DIV_NUM];				//�}�b�v�̎��
	int width;							//��
	int height;							//����
}MAPCHIP;	//MAP_IMAGE�\����

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//�}�b�v�̎��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}MAP;	//MAP�\����

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

FONT FontTanu32;	//���ʂ������}�W�b�N�F�傫��32�@�̃t�H���g�\����

int GameScene;		//�Q�[���V�[�����Ǘ�

IMAGE_BACK ImageBack[IMAGE_BACK_NUM];	//�Q�[���̔w�i

//���������� �v���O�����ǉ��������� ����������������������������������������

IMAGE ImageTitleBK;						//�^�C�g���w�i�̉摜
IMAGE_ROTA ImageTitleROGO;				//�^�C�g�����S�̉摜
IMAGE_BLINK ImageTitleSTART;			//�^�C�g���X�^�[�g�̉摜

//���������� �v���O�����ǉ������܂� ����������������������������������������

CHARA player;		//�Q�[���̃L����

//���y�֘A
MUSIC BGM;			//�Q�[����BGM

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,
		k,k,k,k,k,k,k,k,k,k,k,g,k,	// 0
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 1
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 2
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 3
		k,t,k,k,k,k,k,k,k,k,k,k,k,	// 4
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 5
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 6
		k,t,t,t,t,t,t,t,t,t,t,t,k,	// 7
		k,k,k,k,k,k,k,k,k,k,k,s,k,	// 8
};	//�Q�[���̃}�b�v

//�Q�[���}�b�v�̏�����
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�}�b�v�`�b�v�̉摜���Ǘ�
MAPCHIP mapChip;

//�}�b�v�̏ꏊ���Ǘ�
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�X�^�[�g�̈ʒu
iPOINT startPt{ -1,-1 };

//�}�b�v�̓����蔻��
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

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

BOOL MY_FONT_INSTALL_ONCE(VOID);	//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
BOOL MY_FONT_CREATE(VOID);			//�t�H���g���쐬����
VOID MY_FONT_DELETE(VOID);			//�t�H���g���폜����

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

BOOL MY_LOAD_MUSIC(VOID);		//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);		//���y���܂Ƃ߂č폜����֐�

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);	//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT, RECT);	//�̈�̓����蔻�������֐�

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����
	SetWindowIconID(IDI_ICON1);							//�A�C�R���t�@�C����Ǎ�

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�摜��ǂݍ���
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//���y��ǂݍ���
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//�v���C���[�̐ݒ�
	player.CanShot = TRUE;
	player.ShotReLoadCnt = 0;
	player.ShotReLoadCntMAX = CHARA_RELOAD_LOW;

	//�t�H���g���ꎞ�I�ɃC���X�g�[��
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//�t�H���g�n���h�����쐬
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

	GameScene = GAME_SCENE_START;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

	//�v���C���[�̍ŏ��̈ʒu���A�X�^�[�g�ʒu�ɂ���
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�X�^�[�g�ʒu��T��
			if (mapData[tate][yoko] == s)
			{
				//�X�^�[�g�ʒu���v�Z
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	//���SX���W���擾
				startPt.y = mapChip.height * tate + mapChip.height / 2;	//���SY���W���擾
				break;
			}
		}
		//�X�^�[�g�����܂��Ă���΁A���[�v�I��
		if (startPt.x != -1 && startPt.y != -1) { break; }
	}

	//�X�^�[�g�����܂��Ă��Ȃ����
	if (startPt.x == -1 && startPt.y == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��擾

		MY_MOUSE_UPDATE();						//�}�E�X�̏�Ԃ��擾

		MY_FPS_UPDATE();	//FPS�̏���[�X�V]

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

	//�t�H���g�n���h����j��
	MY_FONT_DELETE();

	//�ꎞ�I�ɃC���X�g�[�������t�H���g���A���C���X�g�[��
	MY_FONT_UNINSTALL_ONCE();

	//�摜�n���h����j��
	MY_DELETE_IMAGE();

	//���y�n���h����j��
	MY_DELETE_MUSIC();

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
	//�}�E�X�̈ȑO�̍��W���擾
	mouse.OldPoint = mouse.Point;

	//�}�E�X�̈ȑO�̃{�^�����͂��擾
	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	//�}�E�X�̍��W���擾
	GetMousePoint(&mouse.Point.x, &mouse.Point.y);

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

//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜(WinAPI)
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}

//�t�H���g��ǂݍ��ފ֐�
//���@���Fconst char *�F�ǂݍ��ރt�H���g�̖��O
//���@���Fint�@�F�t�H���g�̑傫��
//���@���Fint�@�F�t�H���g�̑���
//���@���Fint�@�F�t�H���g�̃^�C�v
//�߂�l�F�Ȃ����ύX���߂�l�FBOOL�F�G���[���FFALSE
BOOL MY_FONT_CREATE(VOID)
{
	//���������ʂ������}�W�b�N�̃t�H���g���쐬������

	//�t�H���g�f�[�^���쐬
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);	//�p�X���R�s�[
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);	//�t�H���g�����R�s�[
	FontTanu32.handle = -1;								//�n���h����������
	FontTanu32.size = 32;								//�T�C�Y��32
	FontTanu32.bold = 1;								//����1
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//�A���`�G�C���A�V���O�t���̃t�H���g

	//�t�H���g�n���h���쐬
	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);
	//�t�H���g�n���h���쐬�ł��Ȃ��Ƃ��A�G���[
	if (FontTanu32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	//���������ʂ������}�W�b�N�̃t�H���g���쐬������

	return TRUE;
}

//�t�H���g���폜����֐�
VOID MY_FONT_DELETE(VOID)
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(FontTanu32.handle);	//�t�H���g�̃n���h�����폜

	return;
}

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
		SetMouseDispFlag(FALSE);			//�}�E�X�J�[�\�����\��

		//�v���C���[�̒��S�ʒu���v�Z����
		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		//�v���C���[�̉摜�̈ʒu��ݒ肷��
		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		//�v���C���[�̓�����ȑO�̈ʒu��ݒ肷��
		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;

		//�X�^�[�g�ʒu���}�E�X�̈ʒu�ɂ���
		SetMousePoint(player.image.x, player.image.y);

		GameScene = GAME_SCENE_PLAY;
	}

	//���������� �v���O�����ǉ��������� ����������������������������������������

	//�^�C�g�����S���g��
	if (ImageTitleROGO.rate < ImageTitleROGO.rateMAX)
	{
		ImageTitleROGO.rate += IMAGE_TITLE_ROGO_ROTA;
	}

	//�^�C�g�����S���ړ�
	if (ImageTitleROGO.image.x < GAME_WIDTH / 2)
	{
		ImageTitleROGO.image.x += IMAGE_TITLE_ROGO_X_SPEED;
	}
	else
	{
		//�^�C�g�����S���ړ�����������

		//�X�^�[�g��_��
		if (ImageTitleSTART.Cnt < ImageTitleSTART.CntMAX)
		{
			ImageTitleSTART.Cnt += IMAGE_TITLE_START_CNT;
		}
		else
		{
			//�`�悷��/���Ȃ������߂�
			if (ImageTitleSTART.IsDraw == FALSE)
			{
				ImageTitleSTART.IsDraw = TRUE;
			}
			else if (ImageTitleSTART.IsDraw == TRUE)
			{
				ImageTitleSTART.IsDraw = FALSE;
			}
			ImageTitleSTART.Cnt = 0;
		}
	}
	//���������� �v���O�����ǉ������܂� ����������������������������������������

	return;
}

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);	//�^�C�g���w�i�̕`��

	//�^�C�g�����S����]���Ȃ���`��
	DrawRotaGraph(
		ImageTitleROGO.image.x, ImageTitleROGO.image.y,	//�摜�̍��W
		ImageTitleROGO.rate,							//�摜�̊g�嗦
		ImageTitleROGO.angle,							//�摜�̉�]��
		ImageTitleROGO.image.handle, TRUE);				//�摜�̃n���h��

	//�_��
	if (ImageTitleSTART.IsDraw == TRUE)
	{
		//�^�C�g���X�^�[�g�̕`��
		DrawGraph(ImageTitleSTART.image.x, ImageTitleSTART.image.y, ImageTitleSTART.image.handle, TRUE);
	}

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
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGM���~�߂�
		}

		SetMouseDispFlag(TRUE);		//�}�E�X�J�[�\����\��

		GameScene = GAME_SCENE_END;

		return;	//�����I�ɃG���h��ʂɔ��
	}

	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(BGM.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, BGM.handle);	//50%�̉��ʂɂ���

		//BGM�𗬂�
		//DX_PLAYTYPE_NORMAL:�@�m�[�}���Đ�
		//DX_PLAYTYPE_BACK  : �o�b�N�O���E���h�Đ�
		//DX_PLAYTYPE_LOOP  : ���[�v�Đ�
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	//�}�E�X���E�N���b�N����ƁA�^�C�g����ʂɖ߂�
	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		//�N���b�N�������W���擾���Ă���
		iPOINT R_ClickPt = mouse.Point;

		//�}�E�X��\��
		SetMouseDispFlag(TRUE);

		//�I���_�C�A���O��\��
		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)		//YES�Ȃ�A�Q�[���𒆒f����
		{
			//BGM������Ă���Ȃ�
			if (CheckSoundMem(BGM.handle) != 0)
			{
				StopSoundMem(BGM.handle);	//BGM���~�߂�
			}

			SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��

			//�����I�Ƀ^�C�g����ʂɔ��
			GameScene = GAME_SCENE_START;
			return;

		}
		else if (Ret == IDNO)	//NO�Ȃ�A�Q�[���𑱍s����
		{
			//�}�E�X�̈ʒu���A�N���b�N����O�ɖ߂�
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			//�}�E�X���\���ɂ���B
			SetMouseDispFlag(FALSE);
		}
	}

	//��ʓ��Ƀ}�E�X�������
	if (mouse.Point.x >= 0 && mouse.Point.x <= GAME_WIDTH
		&& mouse.Point.y >= 0 && mouse.Point.y <= GAME_HEIGHT)
	{
		//�}�E�X�̓�����O�̈ʒu����A���݈ʒu�̍������̐��l�ȓ��Ȃ�A������
		int MoveValue = 100;

		//�}�E�X�̈ړ��ʂ����Ȃ��Ƃ��ɁA�ړ�������
		if (abs(player.collBeforePt.x - mouse.Point.x) < MoveValue
			&& abs(player.collBeforePt.y - mouse.Point.y) < MoveValue)
		{
			//�v���C���[�̒��S�ʒu��ݒ肷��
			player.CenterX = mouse.Point.x;
			player.CenterY = mouse.Point.y;
		}
		else
		{
			//�v���C���[�̒��S�ʒu��ݒ肷��
			player.CenterX = player.collBeforePt.x;
			player.CenterY = player.collBeforePt.y;

			//�}�E�X�̈ʒu��ݒ肷��
			SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);
		}

	}

	//�v���C���[�̓����蔻��̐ݒ�
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	//�v���C���[�ƃ}�b�v���������Ă�����
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);
		IsMove = FALSE;
	}

	if (IsMove == TRUE)
	{
		//��ʓ��Ƀ}�E�X�������
		if (mouse.Point.x >= 0 && mouse.Point.x <= GAME_WIDTH
			&& mouse.Point.y >= 0 && mouse.Point.y <= GAME_HEIGHT)
		{
			//�v���C���[�̈ʒu�ɒu��������
			player.image.x = player.CenterX - player.image.width / 2;
			player.image.y = player.CenterY - player.image.height / 2;

			//�������Ă��Ȃ��Ƃ��̍��W���擾
			player.collBeforePt.x = player.CenterX;
			player.collBeforePt.y = player.CenterY;
		}
	}

	//�}�E�X�̍��{�^�����N���b�N�����Ƃ�
	if (MY_MOUSE_DOWN(MOUSE_INPUT_LEFT) == TRUE)
	{
		//�V���b�g�����Ă�Ƃ�
		if (player.CanShot == TRUE)
		{
			//�V���b�g���ˁI�I
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			player.CanShot = FALSE;

			//�󂢂Ă���X���b�g�ŁA�e�̕`�������
			for (int cnt = 0; cnt < TAMA_MAX; cnt++)
			{
				if (player.tama[cnt].IsDraw == FALSE)
				{
					//�e��X�ʒu�̓v���C���[�̒��S���甭��
					player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

					//�e��Y�ʒu�̓v���C���[�̏㕔�����甭��
					player.tama[cnt].y = player.image.y;

					//�e��`�悷��
					player.tama[cnt].IsDraw = TRUE;

					break;
				}
			}
		}
	}

	//�V���b�g�����ĂȂ��Ƃ�
	if (player.CanShot == FALSE)
	{
		//�����[�h���Ԃ��I������Ƃ�
		if (player.ShotReLoadCnt == player.ShotReLoadCntMAX)
		{
			player.ShotReLoadCnt = 0;
			player.CanShot = TRUE;		//�ĂуV���b�g�ł���
		}

		player.ShotReLoadCnt++;	//�����[�h����
	}

	//�w�i�摜�𓮂���
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		//�摜���ړ�������
		ImageBack[num].image.y++;

		//�w�i�摜��`��ł��Ȃ��Ƃ�
		if (ImageBack[num].IsDraw == FALSE)
		{
			//�w�i�摜����ʓ��ɂ���Ƃ�
			if (ImageBack[num].image.y + ImageBack[num].image.height > 0)
			{
				ImageBack[num].IsDraw = TRUE;	//�摜��`�悷��
			}
		}

		//�w�i�摜����ʂ�ʂ�z�����Ƃ�
		if (ImageBack[num].image.y > GAME_HEIGHT)
		{
			ImageBack[num].image.y = 0 - ImageBack[0].image.height * 3;	//�摜�̍����Q���A��Ɉړ�������
			ImageBack[num].IsDraw = FALSE;								//�摜��`�悵�Ȃ�
		}
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	//�w�i��`�悷��
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		//�`��ł���Ƃ��́E�E�E
		if (ImageBack[num].IsDraw == TRUE)
		{
			//�w�i��`��
			DrawGraph(ImageBack[num].image.x, ImageBack[num].image.y, ImageBack[num].image.handle, TRUE);

			//�w�i�摜�̐������e�X�g�I�ɕ\��
			DrawFormatString(
				ImageBack[num].image.x,
				ImageBack[num].image.y,
				GetColor(255, 255, 255), "�w�i�摜�F%d", num + 1);
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v��`��
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}

	//�����蔻��̕`��i�f�o�b�O�p�j
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�ǂȂ��
			if (mapData[tate][yoko] == k)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//�ʘH�Ȃ��
			if (mapData[tate][yoko] == t)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}
		}
	}

	//�v���C���[�̂�`�悷��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//�����蔻��̕`��i�f�o�b�O�p�j
	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);

	//�e�̏��𐶐�
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		//�`��ł���e�̏���
		if (player.tama[cnt].IsDraw == TRUE)
		{
			//�e��`�悷��
			DrawGraph(
				player.tama[cnt].x,
				player.tama[cnt].y,
				player.tama[cnt].handle[player.tama[cnt].nowImageKind],	//���݂̉摜�̎�ނɂ������n���h��
				TRUE);

			//�e�̕\���t���[���𑝂₷
			if (player.tama[cnt].changeImageCnt < player.tama[cnt].changeImageCntMAX)
			{
				player.tama[cnt].changeImageCnt++;
			}
			else
			{
				//���ݕ\�����Ă���e�̎�ނ��A�܂�����Ƃ�
				if (player.tama[cnt].nowImageKind < TAMA_DIV_NUM - 1)	//-1���Ȃ��ƁA�Ō�̎�ނ̂Ƃ���++����Ă��܂�
				{
					player.tama[cnt].nowImageKind++;	//�e�����̎�ނɂ���
				}
				else
				{
					player.tama[cnt].nowImageKind = 0;	//�e�̎�ނ����Z�b�g����
				}

				player.tama[cnt].changeImageCnt = 0;
			}

			//�e����Ɉړ�������
			if (player.tama[cnt].y < 0)
			{
				player.tama[cnt].IsDraw = FALSE;	//�`��I��
			}
			else
			{
				player.tama[cnt].y -= player.tama[cnt].speed;
			}
		}
	}

	DrawString(0, 0, "�v���C���(�X�y�[�X�L�[�������ĉ�����)", GetColor(255, 255, 255));
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
		SetMouseDispFlag(TRUE);		//�}�E�X�J�[�\����\��

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

	//���������� �v���O�����ǉ��������� ����������������������������������������

	//�^�C�g���w�i
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);			//�p�X�̐ݒ�
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);			//�ǂݍ���
	if (ImageTitleBK.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);	//�摜�̕��ƍ������擾
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//���E��������
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//�㉺��������

	//�^�C�g�����S
	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);					//�p�X�̐ݒ�
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);			//�ǂݍ���
	if (ImageTitleROGO.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);	//�摜�̕��ƍ������擾
	ImageTitleROGO.image.x = 230;							//�����Ă��镔������`�悵����
	ImageTitleROGO.image.y = GAME_HEIGHT / 2;				//������
	ImageTitleROGO.angle = DX_PI * 2;						//��]��
	ImageTitleROGO.angleMAX = DX_PI * 2;					//��]��MAX
	ImageTitleROGO.rate = 0.0;								//�g�嗦
	ImageTitleROGO.rateMAX = IMAGE_TITLE_ROGO_ROTA_MAX;		//�g�嗦MAX

	//�^�C�g���X�^�[�g
	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);					//�p�X�̐ݒ�
	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);			//�ǂݍ���
	if (ImageTitleSTART.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);	//�摜�̕��ƍ������擾
	ImageTitleSTART.image.x = GAME_WIDTH / 2 - ImageTitleSTART.image.width / 2;					//���E��������
	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height / 2 + 10;	//���S�̉��ɕ\��
	ImageTitleSTART.Cnt = 0.0;								//�J�E���^
	ImageTitleSTART.CntMAX = IMAGE_TITLE_START_CNT_MAX;		//�J�E���^MAX
	ImageTitleSTART.IsDraw = FALSE;							//�`�悳���Ȃ�

	//���������� �v���O�����ǉ������܂� ����������������������������������������

	//�w�i�摜
	strcpy_s(ImageBack[0].image.path, IMAGE_BACK_PATH);			//�p�X�̐ݒ�
	strcpy_s(ImageBack[1].image.path, IMAGE_BACK_REV_PATH);		//�p�X�̐ݒ�(�w�i�摜���])
	strcpy_s(ImageBack[2].image.path, IMAGE_BACK_PATH);			//�p�X�̐ݒ�
	strcpy_s(ImageBack[3].image.path, IMAGE_BACK_REV_PATH);		//�p�X�̐ݒ�(�w�i�摜���])

	//�摜��A�����ēǂݍ���
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		ImageBack[num].image.handle = LoadGraph(ImageBack[num].image.path);	//�ǂݍ���
		if (ImageBack[num].image.handle == -1)
		{
			//�G���[���b�Z�[�W�\��
			MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//�摜�̕��ƍ������擾
		GetGraphSize(ImageBack[num].image.handle, &ImageBack[num].image.width, &ImageBack[num].image.height);
	}
	//�w�i�摜�@�̐ݒ�
	ImageBack[0].image.x = GAME_WIDTH / 2 - ImageBack[0].image.width / 2;	//���E��������
	ImageBack[0].image.y = 0 - ImageBack[0].image.height * 0;				//y�͌��_����
	ImageBack[0].IsDraw = FALSE;

	//�w�i�摜�A�̐ݒ�
	ImageBack[1].image.x = GAME_WIDTH / 2 - ImageBack[1].image.width / 2;	//���E��������
	ImageBack[1].image.y = 0 - ImageBack[0].image.height * 1;				//�摜�̍����P���A��Ɉړ�������
	ImageBack[1].IsDraw = FALSE;

	//�w�i�摜�B�̐ݒ�
	ImageBack[2].image.x = GAME_WIDTH / 2 - ImageBack[2].image.width / 2;	//���E��������
	ImageBack[2].image.y = 0 - ImageBack[0].image.height * 2;				//�摜�̍����Q���A��Ɉړ�������
	ImageBack[2].IsDraw = FALSE;

	//�w�i�摜�B�̐ݒ�
	ImageBack[3].image.x = GAME_WIDTH / 2 - ImageBack[2].image.width / 2;	//���E��������
	ImageBack[3].image.y = 0 - ImageBack[0].image.height * 3;				//�摜�̍����R���A��Ɉړ�������
	ImageBack[3].IsDraw = FALSE;

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
	player.speed = CHARA_SPEED_LOW;									//�X�s�[�h��ݒ�

	//�Ԓe�̉摜�𕪊�����
	int tamaRedRes = LoadDivGraph(
		TAMA_RED_PATH,										//�Ԓe�̃p�X
		TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO,			//�Ԓe�𕪊����鐔
		TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,					//�摜�𕪊�����̕��ƍ���
		&player.tama[0].handle[0]);							//���������摜������n���h��

	if (tamaRedRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), TAMA_RED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(player.tama[0].handle[0], &player.tama[0].width, &player.tama[0].height);

	//�e�̏��𐶐�
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		//�p�X���R�s�[
		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));

		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{
			//�n���h�����R�s�[
			player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
		}

		//�����R�s�[
		player.tama[cnt].width = player.tama[0].width;

		//�������R�s�[
		player.tama[cnt].height = player.tama[0].height;

		//�e��X�ʒu�̓v���C���[�̒��S���甭��
		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		//�e��Y�ʒu�̓v���C���[�̏㕔�����甭��
		player.tama[cnt].y = player.image.y;

		//�e�͍ŏ��͔�\��
		player.tama[cnt].IsDraw = FALSE;

		//�e�̕\���J�E���g��0�ɂ���
		player.tama[cnt].changeImageCnt = 0;

		//�e�̕\���J�E���gMAX��ݒ肷��
		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

		//���݂̉摜�̎�ނ�����������
		player.tama[cnt].nowImageKind = 0;

		//�e�̃X�s�[�h��ݒ肷��
		player.tama[cnt].speed = CHARA_SPEED_LOW;
	}

	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//�Ԓe�̃p�X
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//�Ԓe�𕪊����鐔
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//�摜�𕪊�����̕��ƍ���
		&mapChip.handle[0]);								//���������摜������n���h��

	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�f�[�^�������p�ɏ����R�s�[
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//�}�b�v�̎�ނ��R�s�[
			map[tate][yoko].kind = mapData[tate][yoko];

			//�}�b�v�̕��ƍ������R�s�[
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//�}�b�v�̍��W��ݒ�
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�̓����蔻���ݒ�
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	return TRUE;
}

//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		DeleteGraph(ImageBack[0].image.handle);
	}

	DeleteGraph(player.image.handle);

	//���������� �v���O�����ǉ��������� ����������������������������������������

	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);

	//���������� �v���O�����ǉ������܂� ����������������������������������������

	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }

	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

//���y���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_MUSIC(VOID)
{
	//�w�i���y
	strcpy_s(BGM.path, MUSIC_BGM_PATH);		//�p�X�̐ݒ�
	BGM.handle = LoadSoundMem(BGM.path);	//�ǂݍ���
	if (BGM.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�v���C���[�̃V���b�g��
	strcpy_s(player.musicShot.path, MUSIC_PLAYER_SHOT_PATH);			//�p�X�̐ݒ�
	player.musicShot.handle = LoadSoundMem(player.musicShot.path);		//�ǂݍ���
	if (player.musicShot.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//���y���܂Ƃ߂č폜����֐�
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(player.musicShot.handle);

	return;
}

//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
				if (map[tate][yoko].kind == k) { return TRUE; }
			}
		}
	}

	return FALSE;
}

//�̈�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//�������Ă���
	}

	return FALSE;		//�������Ă��Ȃ�
}