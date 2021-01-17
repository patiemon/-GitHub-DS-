#include "DxLib.h"
#include <time.h>

//########## マクロ定義 ##########
#define GAME_WIDTH			800	//画面の横の大きさ
#define GAME_HEIGHT			600	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"	//ウィンドウのタイトル



#define GAME_FPS			60	//FPSの数値	

#define PATH_MAX            100

//---------------------------------------------------------------------------------------------------------画像系define文--------------------//

#define IMAGE_PLAY_BK_PATH			TEXT(".\\IMAGE\\PLAY_BK.png")		//タイトル背景の画像
#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\TITLE_BK.png")		//タイトル背景の画像
#define IMAGE_PLAYER_PATH		    TEXT(".\\IMAGE\\PLAYER.png")	//プレイヤーの画像
#define IMAGE_DINO1_PATH            TEXT(".\\IMAGE\\DINO1.png")


#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")



typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}IMAGE;	//画像構造体

//マウスのボタン
#define MOUSE_BUTTON_CODE	129		//0x0000～0x0080まで

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン

enum CHARA_SPEED {
	CHARA_SPEED_RELOAD = 1,
	CHARA_SPEED_REX = 2,
	CHARA_SPEED_USE = 5
};	//キャラクターのスピード

enum DINO_SPEED {
	DINO_SPEED_WARK = 1,
	DINO_SPEED_NORMAL = 4,
	DINO_SPPED_ANGRY = 5
};

typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE構造体
	int speed;					//速さ
	int CenterX;				//中心X
	int CenterY;				//中心Y

	int JumpNowY;
	int JumpRakkaY;

	BOOL CanJump;

}CHARA;	//キャラクター構造体

typedef struct STRUCT_DINO
{
	IMAGE image;				//IMAGE構造体
	int speed;					//速さ
	int CenterX;				//中心X
	int CenterY;				//中心Y

	int JumpNowY;
	int JumpRakkaY;

	BOOL CanJump;
	BOOL CanMove;
	BOOL DinoMove;

}DINO;	//敵キャラ構造体

//int型のPOINT構造体
typedef struct STRUCT_I_POINT
{
	int x = -1;	//座標を初期化
	int y = -1;	//座標を初期化
}iPOINT;

//マウス構造体
typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInputの値を入れる
	int WheelValue = 0;	//マウスホイールの回転量(奥はプラス値 / 手前はマイナス値)
	iPOINT Point;		//マウスの座標が入る
	iPOINT OldPoint;	//マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力(直前)が入る
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力が入る
}MOUSE;

//########## グローバル変数 ##########
//FPS関連
int StartTimeFps;				//測定開始時刻
int CountFps;					//カウンタ
float CalcFps;					//計算結果
int SampleNumFps = GAME_FPS;	//平均を取るサンプル数

//キーボードの入力を取得
char AllKeyState[256] = { '\0' };			//すべてのキーの状態が入る
char OldAllKeyState[256] = { '\0' };	//すべてのキーの状態(直前)が入る

//マウスの座標を取得
MOUSE mouse;


int GameScene;		//ゲームシーンを管理

IMAGE ImageBack;		//ゲームの背景
IMAGE ImageTitleBK;		//タイトル背景の画面
CHARA player;			//ゲームのキャラ
DINO dino;				//ゲームの敵キャラ


//########## プロトタイプ宣言 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する
BOOL MY_KEY_UP(int);				//キーを押し上げたか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int, int);		//キーを押し続けているか、キーコードで判断する

VOID MY_MOUSE_UPDATE(VOID);			//マウスの入力情報を更新する
BOOL MY_MOUSE_DOWN(int);			//ボタンを押しているか、マウスコードで判断する
BOOL MY_MOUSE_UP(int);				//ボタンを押し上げたか、マウスコードで判断する
BOOL MY_MOUSEDOWN_KEEP(int, int);	//ボタンを押し続けているか、マウスコードで判断する	

VOID MY_START(VOID);		//スタート画面
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

VOID MY_PLAY(VOID);			//プレイ画面
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画

VOID MY_END(VOID);			//エンド画面
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);		//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);		//画像をまとめて削除する関数

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	if (MY_LOAD_IMAGE() == FALSE) { return -1; } //画像を読み込む

	SetMouseDispFlag(TRUE);			//マウスカーソルを表示	

    player.CanJump = TRUE;
	dino.CanJump = TRUE;
	dino.CanMove = TRUE;

	int DrawX = 0;	//表示位置X
	int DrawY = 0;	//表示位置Y

	iPOINT InputFirst = { 0,0 };	//始点
	iPOINT InputEnd = { 0,0 };		//終点
	BOOL IsMouseDownLeft = FALSE;	//マウスの左ボタンを押したか

	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		MY_MOUSE_UPDATE();						//マウスの状態を取得

		MY_FPS_UPDATE();	//FPSの処理[更新]


		if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE) { mouse.Point.x++; }
		if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE) { mouse.Point.x--; }

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//スタート画面
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//プレイ画面
			break;
		case GAME_SCENE_END:
			MY_END();	//エンド画面
			break;
		}

		MY_FPS_DRAW();		//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	MY_DELETE_IMAGE();	

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

//########## FPS値を計測、更新する関数 ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS値を描画する関数 ##########
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS値を計測し、待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	//参考：https://dxlib.xsrv.jp/function/dxfunc_input.html

	char TempKey[256];	//一時的に、現在のキーの入力状態を格納する

	//直前のキー入力をとっておく
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押し上げたか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

//キーを押し続けているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
//引　数：int：キーを押し続ける時間
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//マウスの入力情報を更新する
VOID MY_MOUSE_UPDATE(VOID)
{

	//マウスの以前のボタン入力を取得
	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	//マウスの押しているボタンを取得
	mouse.InputValue = GetMouseInput();

	//左ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }		//押している
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }		//押していない

	//中ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }	//押している
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }	//押していない

	//右ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }		//押している
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }	//押していない

	//ホイールの回転量を取得
	mouse.WheelValue = GetMouseWheelRotVol();

	return;
}

//ボタンを押しているか、マウスーコードで判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	//マウスコードのボタンを押している時
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;	//ボタンを押している
	}
	else
	{
		return FALSE;	//ボタンを押していない
	}
}

//ボタンを押し上げたか、マウスコード判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1	//直前は押していて
		&& mouse.Button[MOUSE_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//ボタンを押し上げている
	}
	else
	{
		return FALSE;	//ボタンを押し上げていない
	}
}

//ボタンを押し続けているか、マウスコード判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
//引　数：int：ボタンを押し続ける時間
BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//フォントを読み込む関数
//引　数：const char *：読み込むフォントの名前
//引　数：int　：フォントの大きさ
//引　数：int　：フォントの太さ
//引　数：int　：フォントのタイプ
//戻り値：なし→変更→戻り値：BOOL：エラー時：FALSE

//▼▼▼▼▼ プログラム追加ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	//エンターキーを押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_PLAY;
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageBack.x, ImageBack.y, ImageTitleBK.handle, TRUE);

	DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//プレイ画面の処理
	MY_PLAY_DRAW();	//プレイ画面の描画

	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{
	//スペースキーを押したら、エンドシーンへ移動する
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
		srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
		dino.DinoMove = rand() % 3 + 1; // 1～3の乱数生成
		dino.CanMove = false;
	}

	//rand関数サンプルテキスト
	//for (int i = 0; i < 3; i++) {
	//	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
	//	printf("%d回目の乱数発生: ", i + 1);

	//	// 1から10までの乱数を発生
	//	for (int j = 0; j < 3; j++) {
	//		printf("%d, ", rand() % 10 + 1);
	//	}
	//	sleep(1); // time関数で取得する時刻を変えるために1秒待機
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

	//プレイヤーの位置に置き換える
	player.image.x = player.CenterX - player.image.width / 2;
	player.image.y = player.CenterY - player.image.height / 2;

	dino.image.x = dino.CenterX - dino.image.width / 2;
	dino.image.y = dino.CenterY - dino.image.height / 2;

	//画面外にプレイヤーが行かないようにする
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

	////画面外にプレイヤーが行かないようにする
	//if (player.image.x < 0) { player.image.x = 0; }
	//if (player.image.x + player.image.width > GAME_WIDTH) { player.image.x = GAME_WIDTH - player.image.width; }
	//if (player.image.y < 0) { player.image.y = 0; }
	//if (player.image.y + player.image.height > GAME_HEIGHT) { player.image.y = GAME_HEIGHT - player.image.height; }

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);

	//DrawExtendGraph(
	//	player.image.x, player.image.y,														//ココから
	//	player.image.x + player.image.width * 2, player.image.y + player.image.height * 2,	//ココまで引き伸ばす
	//	player.image.handle, TRUE);

	DrawGraph(
		player.image.x , player.image.y , player.image.handle , TRUE
	);

	DrawBox(player.image.x, player.image.y, player.image.x + player.image.width, player.image.y + player.image.height, GetColor(255, 255, 255), FALSE);

	//DrawExtendGraph(
	//	dino.image.x, dino.image.y,														//ココから
	//	dino.image.x + dino.image.width * 2, dino.image.y + dino.image.height * 2,	//ココまで引き伸ばす
	//	dino.image.handle, TRUE);

	DrawGraph(
		dino.image.x, dino.image.y, dino.image.handle, TRUE
	);

	DrawBox(dino.image.x, dino.image.y, dino.image.x + dino.image.width, dino.image.y + dino.image.height, GetColor(255, 255, 255), FALSE);

	DrawString(0, 0, "プレイ画面(Iキーを押して下さい)", GetColor(255, 255, 255));

	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画
	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	//エスケープキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	//青の四角を描画
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

	DrawString(0, 0, "エンド画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//画像をまとめて読み込む関数
BOOL MY_LOAD_IMAGE(VOID)
{
	//背景画像
	strcpy_s(ImageBack.path, IMAGE_PLAY_BK_PATH);		//パスの設定
	ImageBack.handle = LoadGraph(ImageBack.path);	//読み込み
	if (ImageBack.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);			//パスの設定
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);			//読み込み
	if (ImageTitleBK.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(ImageBack.handle, &ImageBack.width, &ImageBack.height);	//画像の幅と高さを取得
	ImageBack.x = GAME_WIDTH / 2 - ImageBack.width / 2;		//左右中央揃え
	ImageBack.y = GAME_HEIGHT / 2 - ImageBack.height / 2;	//上下中央揃え

	//プレイヤーの画像
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//パスの設定
	player.image.handle = LoadGraph(player.image.path);	//読み込み
	if (player.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//画像の幅と高さを取得
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//左右中央揃え
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//上下中央揃え
	player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す
	player.speed = CHARA_SPEED_USE;




	strcpy_s(dino.image.path, IMAGE_DINO1_PATH);		//パスの設定
	dino.image.handle = LoadGraph(dino.image.path);	//読み込み
	if (dino.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_DINO1_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(dino.image.handle, &dino.image.width, &dino.image.height);	//画像の幅と高さを取得
	dino.image.x = GAME_WIDTH / 2 - dino.image.width / 2;		//左右中央揃え
	dino.image.y = GAME_HEIGHT / 2 - dino.image.height / 2;		//上下中央揃え
	dino.CenterX = dino.image.x + dino.image.width / 2;		//画像の横の中心を探す
	dino.CenterY = dino.image.y + dino.image.height / 2;		//画像の縦の中心を探す
	dino.speed = DINO_SPEED_NORMAL;




//	//敵キャラの画像
//	strcpy_s(dino.image.path, IMAGE_DINO1_PATH);		//パスの設定
//	dino.image.handle = LoadGraph(dino.image.path);	//読み込み
//	if (dino.image.handle == -1)
//	{
//		//エラーメッセージ表示
//		MessageBox(GetMainWindowHandle(), IMAGE_DINO1_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(dino.image.handle, &dino.image.width, &dino.image.height);	//画像の幅と高さを取得
//	dino.image.x = GAME_WIDTH / 2 - dino.image.width / 2;		//左右中央揃え
//	dino.image.y = GAME_HEIGHT / 2 - dino.image.height / 2;		//上下中央揃え
//	dino.CenterX = dino.image.x + dino.image.width / 2;		//画像の横の中心を探す
//	dino.CenterY = dino.image.y + dino.image.height / 2;		//画像の縦の中心を探す
//	dino.speed = DINO_SPEED_NORMAL;

	return TRUE;
}

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageBack.handle);          //プレイ画面削除
	DeleteGraph(ImageTitleBK.handle);       //タイトル画面削除
//	DeleteGraph(player.image.handle);

	return;
}

