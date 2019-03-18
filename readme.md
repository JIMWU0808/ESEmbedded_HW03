HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

-------------------
## hw03
# 1.實驗題目
1.撰寫簡易c語言並觀察其組語、暫存器、記憶體的變化
# 2.實驗步驟
1. 先將資料夾 gnu-mcu-eclipse-qemu 完整複製到 ESEmbedded_HW03 資料夾中
2. 寫個c語言的簡單程式
3. make之後觀察其組語和使用make qemu觀察暫存器與記憶體的狀態
4. 設計程式 main.c並將其變成組語之後觀察 c function 傳遞與回傳參數與使用make qemu觀察暫存器與記憶體的變化


main.c:
```
void reset_handler(void)
{
	int i,j,k;
        k=1;
	j=0;
	for(i=0;i<10;i++)
	{
		j+=i;
		k*=i;
	}
	plus(j,k);
	while (1)
		;
}
int plus(int j,int k)
{
	return j+k;
}
```

轉換成組語
![](https://github.com/JIMWU0808/ESEmbedded_HW03/blob/master/img/3-1.png)

![](https://github.com/JIMWU0808/ESEmbedded_HW03/blob/master/img/3-2.png)
8 :把當前狀態儲存到 0x200000fc & 0x200000f8

a :空出四個儲存位置

c :暫存器r3＝1

e :把r3的值存到r7+4的位置                           到18同理

1c、1e、20：j＋＝i

22、24、26：k＊＝i

2e、30：i＋＋

32、34、36、38：for迴圈判斷

3a、3c、3e ：呼叫函式

42 ：while無限迴圈

44 ～54 ：函式本身功能

56、58 ：返回原本記憶體位置

5a  ：根據 &ARM的指令集指示 ldr這個指令通常都是作加载指令的，但是它也可以作偽指令。一般來說有*＝*為偽指令。  可以使用 .W 寬度說明符強制 LDR 在 Thumb-2 代碼中生成 32 位指令。LDR.W 始终生成 32 位元指令。在這裡式用來加载寄存器。 地址为 pc 加偏移量。

5e  ： 跳回原本函式

![](https://github.com/JIMWU0808/ESEmbedded_HW03/blob/master/img/3-3.png)
最後算出來的答案，分別存在r1、r2、r3中


# 3.结果與討論
這次做完之後大概了解一點c語言和組語和一些組語特殊的指令
