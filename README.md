# Lolidance
整活之作, 灵感来与 [bilibili](https://www.bilibili.com/video/BV1u8411k7BD/)

https://github.com/harisonkhlil/Lolidance/assets/70578017/cc933004-3594-4f43-bedd-daadd312161f

> 通过 `OpenCV` 提取视频帧, 制作 ASCII 字符, ASCII 输出有一定间隔以致无法对齐

## 注意事项

1. 字体大小不要太大, 最好设置为 13-14
2. 需要完备的编译库支持

## 编译前的准备

1. `xcode`: `xcode-select install`
2. `Homebrew`: `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
3. `Cmake`: `brew install cmake`
4. `OpenCV`: `brew install opencv`
5. `LLVM`: `brew install llvm`
6. `Ninga`: `brew install ninga`

## 编译

```sh
cd ${HOME}/Downloads/Lolidance
mkdir build
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE  -DCMAKE_CXX_COMPILER:FILEPATH=/opt/homebrew/opt/llvm/bin/clang++ -G Ninja -S${HOME}/Downloads/Lolidance -B${HOME}/Downloads/Lolidance/build
cmake --build --config Release --target all ${HOME}/Downloads/Lolidance/build
./build/videoCapture
./build/Lolidance
```
Enjoy!!!
