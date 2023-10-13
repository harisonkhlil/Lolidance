#include <csignal>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

const int IMAGE_COUNT = 839; // 图像总数
const int ELEMENT_COUNT = 160 * 45;
const std::string IMAGE_FOLDER = "ASCII";
const char *AUDIO_FILE = "loli.mp3"; // 音频文件名
const int SLEEP_MICROSECONDS = 38000; // 图像切换时的等待时间，单位微秒

volatile sig_atomic_t g_stop = 0; // 用于中断处理的标志

void SignalHandler(int signum) {
    if (signum == SIGINT) {
        g_stop = 1; // 当收到中断信号时设置中断标志
    }
}

void MoveCursorTo(int x, int y) {
    std::cout << "\033[" << y + 1 << ";" << x + 1 << "H"; // 移动光标到指定位置
}

void HideTerminalCursor() {
    std::cout << "\033[?25l"; // 隐藏终端光标
}

void SetTerminalWindowSize(int width, int height) {
    std::cout << "\033[8;" << height << ";" << width << "t"; // 设置终端窗口大小
}

void PlayAudio(const char *filename) {
    char command[100];
    snprintf(command, sizeof(command), "afplay %s &",
             filename); // 播放音频的命令

    int result = system(command);
    if (result != 0) {
        std::cerr << "Error: Unable to play audio."
                  << std::endl; // 播放音频出错时输出错误信息
    }
}

void DisplayImageFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filename
                  << std::endl; // 打开图像文件出错时输出错误信息
        return;
    }

    char data[ELEMENT_COUNT];
    file.read(data, ELEMENT_COUNT);

    if (!file) {
        std::cerr << "Error: Reading file " << filename << " failed."
                  << std::endl; // 读取图像文件出错时输出错误信息
        return;
    }

    std::cout.write(data, ELEMENT_COUNT); // 将图像数据写入终端
}

int main() {
    HideTerminalCursor();          // 隐藏终端光标
    PlayAudio(AUDIO_FILE);         // 播放音频
    signal(SIGINT, SignalHandler); // 设置中断信号处理函数

    int i = 1;

    while (!g_stop && i <= IMAGE_COUNT) {
        std::string imageFileName = "./" + IMAGE_FOLDER + "/Loli-" +
                                    std::to_string(i) +
                                    ".txt"; // 构建当前图像文件的路径
        MoveCursorTo(0, 0);                 // 将光标移动到屏幕左上角
        DisplayImageFromFile(imageFileName); // 显示图像
        std::this_thread::sleep_for(
            std::chrono::microseconds(SLEEP_MICROSECONDS)); // 等待一段时间
        i++;
    }

    system("pkill afplay"); // 停止音频播放

    return 0;
}
