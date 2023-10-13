#include <csignal>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

// 定义常量
constexpr int SCALE_FACTOR = 1;  // 图像缩放因子，1 表示不缩放
constexpr int IMAGE_COUNT = 839; // 图像总数
constexpr int ELEMENT_COUNT =
    (SCALE_FACTOR == 1) ? 194 * 54
                        : 124 * 40; // 每个图像的元素数量，根据缩放因子决定
constexpr int SLEEP_MICROSECONDS = 38000; // 图像切换时的等待时间，单位微秒
const std::string IMAGE_FOLDER = "ASCII";  // 图像的文件夹
const std::string AUDIO_FILE = "loli.mp3"; // 音频文件名

// 中断处理标志
volatile sig_atomic_t g_stop = 0;

// 中断信号处理函数
void SignalHandler(int signum) {
    if (signum == SIGINT) {
        g_stop = 1; // 当收到中断信号时设置中断标志
    }
}

// 从文件显示图像
void DisplayImageFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "错误：无法打开文件 " << filename << std::endl;
        return;
    }

    char data[ELEMENT_COUNT];
    file.read(data, ELEMENT_COUNT);

    if (!file) {
        std::cerr << "错误：读取文件 " << filename << " 失败。" << std::endl;
        return;
    }

    std::cout.write(data, ELEMENT_COUNT); // 将图像数据写入终端
}

// 显示单个图像
void DisplayImage(int imageNumber) {
    std::string imageFileName =
        "./" + IMAGE_FOLDER + "/Loli-" + std::to_string(imageNumber) + ".txt";
    std::this_thread::sleep_for(SLEEP_MICROSECONDS * 1us);
    std::cout << "\033[H"; // 移动光标到屏幕左上角
    DisplayImageFromFile(imageFileName);
}

int main() {
    if (SCALE_FACTOR == 1) {
        std::cout << "\033[8;55;200t"; // 设置终端窗口大小
    } else {
        std::cout << "\033[8;45;130t";
    }

    std::cout << "\033[?25l"; // 隐藏终端光标

    // 在单独线程中播放音频
    std::thread audioThread([]() { system(("afplay " + AUDIO_FILE).c_str()); });
    signal(SIGINT, SignalHandler); // 设置中断信号处理函数
    std::vector<std::thread> imageThreads;

    // 启动图像显示线程
    for (int i = 1; !g_stop && i <= IMAGE_COUNT; i++) {
        imageThreads.emplace_back(DisplayImage, i);
        std::this_thread::sleep_for(SLEEP_MICROSECONDS * 1us);
    }

    audioThread.join(); // 等待音频线程结束

    // 等待所有图像线程完成
    for (std::thread &thread : imageThreads) {
        thread.join();
    }

    return 0;
}
