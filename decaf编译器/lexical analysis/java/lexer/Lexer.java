package lexer;

import java.io.IOException;
import java.util.*;
/*
 * 一个简单的用数组实现的队列
 * 用以保存前看失败时抛弃的字符
 */
class Queue{
	private int capacity = 50;
	private int first=0,last=0;
	private char [] data = new char[capacity];
	public void enqueue(char c) {
		data[last++]=c;
		expand();
		move();
	}
	public char dequeue() {
		return data[first++];
	}
	public char top() {
		return data[first];
	}
	public void move() {
		if(last==capacity-2) {
			for(int i=first; i<last ; i++)
				data[i-first]=data[i];
		}
	}
	public void expand() {
		if( (last-first)<capacity*3/4 )
			return;
		capacity*=2;
		char [] d = new char[capacity];
		for(int i=first; i<last; i++)
			d[i-first]=data[i];
		data = d;
	}
	
	public boolean isEmpty() {
		return first==last;
	}
}
/*
 * 词法分析器主体，对输入的源程序进行词法分析
 * 用一个名为words的哈希表保存关键字，将关键字字符串和对应的TAG作映射
 * 在检测时可以方便地计算一个字符串是否在哈希表中有，即能够快速判断是否是关键字
 * reserve函数向哈希表中添加 关键字——TAG 对
 * readch函数：
 * 		不含参数的版本负责向peek写入当前检测的字符
 * 		含参数的版本负责将下一个字符和参数c作比较判断是否相同
 * scan函数不断读取字符并根据字符类型进行判断，是词法分析器的主要函数
 */
public class Lexer {
	
	private static Queue queue= new Queue();
	public static int line = 1;
	char peek = ' ';
	Hashtable words = new Hashtable();

	void reserve(Word w) {
		words.put(w.lexeme, w);
	}

	public Lexer() {
		reserve(new Word("if", Tag.IF));
		reserve(new Word("else", Tag.ELSE));
		reserve(new Word("while", Tag.WHILE));
		reserve(new Word("do", Tag.DO));
		reserve(new Word("break", Tag.BREAK));
		
		reserve(new Word("void", Tag.VOID));
		reserve(new Word("int", Tag.INT));
		reserve(new Word("double", Tag.DOUBLE));
		reserve(new Word("bool", Tag.BOOL));
		reserve(new Word("string", Tag.STRING));
		reserve(new Word("class", Tag.CLASS));
		reserve(new Word("null", Tag.NULL));
		reserve(new Word("this", Tag.THIS));
		reserve(new Word("extends", Tag.EXTENDS));
		reserve(new Word("for", Tag.FOR));
		reserve(new Word("return", Tag.RETURN));
		reserve(new Word("new", Tag.NEW));
		reserve(new Word("NewArray", Tag.NEWARRAY));
		reserve(new Word("Print", Tag.PRINT));
		reserve(new Word("ReadInteger", Tag.READINTEGER));
		reserve(new Word("ReadLine", Tag.READERLINE));
		reserve(new Word("static", Tag.STATIC));
		
		reserve(Word.True);
		reserve(Word.False);
	}

	public void readch() throws IOException {
		peek = (char) System.in.read();
	}

	boolean readch(char c) throws IOException {
		readch();
		if (peek != c) {
			return false;
		}
		peek = ' ';
		return true;
	}

	public Token scan() throws IOException {
		/*
		 * 忽略空白符、制表符、换行符
		 */
		if(queue.isEmpty())
			for (;; readch()) {
				if (peek == ' ' || peek == '\t')
					continue;
				else if (peek == '\n') {
					line += 1;
				} else {
					break;
				}
			}
		else {
			boolean getNew = true;
			while(!queue.isEmpty()) {
				peek = queue.dequeue();
				if(peek!=' '&&peek!='\t'&&peek!='\r'&&peek!='\n') {
					getNew = false;
					break;
				}
			}
			if(queue.isEmpty()&&getNew)
				getNext();
		}
		/*
		 * 处理注释：
		 * 	1. 单行注释 //
		 * 	2. 块注释  / *  * / 不允许嵌套，只将第一个/ * 和第一个* /配对
		 */
		if(peek=='/') {
			queue.enqueue(peek);
			readch();
			if(peek=='/'||peek=='*') {
				queue.dequeue();
				//   处理单行注释
				if(peek=='/') {
					while(!readch('\n'));
				}
				//   处理块注释
				if(peek=='*') {
					readch();
					char a=peek;
					readch();
					while( !(a=='*'&&peek=='/') ) {
						a=peek;
						readch();
					}
				}
				getNext();
			}
			//  并非注释，可能是除号或其它符号，将除号恢复，保存刚刚取出的字符
			else {
				queue.enqueue(peek);
				peek=queue.dequeue();
			}
		}
		/*
		 * 处理操作符，判断是单个字符还是复合运算符
		 */
		switch (peek) {
		case '&':
			if (readch('&'))
				return Word.and;
			else
				return new Token('&');
		case '|':
			if (readch('|'))
				return Word.or;
			else
				return new Token('|');
		case '=':
			if (readch('='))
				return Word.eq;
			else
				return new Token('=');
		case '!':
			if (readch('='))
				return Word.ne;
			else
				return new Token('!');
		case '<':
			if (readch('='))
				return Word.le;
			else
				return new Token('<');
		case '>':
			if (readch('='))
				return Word.ge;
			else
				return new Token('>');
		case '@':
			System.out.println("@is invalid");
		}
		/*
		 * 对数字进行识别
		 * 识别规则：
		 * 	1. 数字分为十进制和十六进制，十六进制以0x或0X开头
		 * 	2. 可带有小数点，小数点后可以不带有数字
		 * 	3. 可带有指数E或e， 后可接 '+' '-'代表后面指数的正负，而后是一串十进制数字，可带有小数
		 * 	4. 小数点前必须有数字
		 *  
		 *  可能的最长匹配模式：  0 x num1 . num2 E num3 . num4
		 */
		if (Character.isDigit(peek)) {
			boolean real=false;
			int nega=1;
			int v = 0;
			// 分析连续数字部分（10进制）
			do {
				v = 10 * v + Character.digit(peek, 10);
				readch();
			} while (Character.isDigit(peek));	
			if (peek != '.' && peek!= 'E'&& peek!= 'e'&& peek!= 'x'&& peek!= 'X')
				return new Num(v);
			// 分析连续数字部分（16进制）
			if(v==0 && (peek=='X'||peek=='x')) {
				readch();
				do {
					v = 16 * v + Character.digit(peek, 16);
					readch();
				} while (Character.isDigit(peek)||(peek<='f'&&peek>='a'));
			}
			if (peek != '.' && peek!= 'E'&& peek!= 'e')
				return new Num(v);
			// 分析小数部分
			float x = v;
			if(peek=='.') {
				x = getReal(v);
				real=true;
			}
			if (peek!= 'E'&& peek!= 'e')
				return real==false?new Num(v):new Real(x);
			// 分析指数部分
			readch();
			if(peek=='+'||peek=='-') {
				if(peek=='-')
					nega=-1;
				readch();
			}
			float n1= getNum();	
			boolean check = Math.abs(n1+1)>1e-6;
			if(peek=='.'&& check ) {
				float y = getReal((int)n1);
				n1=y;
				real=true;
			}
			else if (check==false){
				n1=0;
			}
			if(real==false&&nega==1)
				return new Num((int) (x*Math.pow(10,nega*n1)));
			else
				return new Real((float) (x*Math.pow(10,nega*n1)));
		}
		
		/*
		 * 识别标识符，识别规则：
		 * 	1. 可包含英文字符（大小写）、数字、下划线
		 * 	2. 必须以英文字符开头
		 * 	3. 大小写敏感
		 */
		if (Character.isLetter(peek)) {
			StringBuffer b = new StringBuffer();
			do {
				b.append(peek);
				readch();
			} while (Character.isLetterOrDigit(peek)||peek=='_');
			String s = b.toString();
			Word w = (Word) words.get(s);
			if (w != null)
				return w;
			w = new Word(s, Tag.ID);
			words.put(s, w);
			return w;
		}
		/*
		 * 识别字符串，识别规则：
		 * 	1. 以双引号开头，以双引号结尾，一对双引号内除了双引号和换行符之间的均视为字符串
		 * 	2. 未完结的字符串换行无效，下一行不视为上一个字符串的后序
		 */
		if(peek=='"') {
			readch();
			StringBuffer b = new StringBuffer();
			do {
				b.append(peek);
				readch();
			} while (peek!='"'&&peek!='\n');
			readch();
			if(b.charAt(b.length()-1)=='\n'||b.charAt(b.length()-1)=='\r')
				b.deleteCharAt(b.length()-1);
			String s = b.toString();
			Word w = new Word(s, Tag.STR);
			words.put(s, w);
			return w;
		}
		
		Token tok = new Token(peek);
		peek = ' ';
		return tok;
	}
	private int getNum() throws IOException {
		int v = 0;
		boolean check = false;
		while (Character.isDigit(peek)) {
			check = true;
			v = 10 * v + Character.digit(peek, 10);
			readch();
		} 
		if(check==true)
			return v;
		return -1;
	}
	private float getReal( int v ) throws IOException{
		float x = v;
		float d = 10;
		for (;;) {
			readch();
			if (!Character.isDigit(peek))
				break;
			x = x + Character.digit(peek, 10) / d;
			d = d * 10;
		}
		return x;
	}
	private void getNext()throws IOException {
		readch();
		for (;; readch()) {
			if (peek == ' ' || peek == '\t')
				continue;
			else if (peek == '\n') {
				line += 1;
			} else {
				break;
			}
		}
	}
	public void out() {
		System.out.println(words.size());
	}

	public char getPeek() {
		return peek;
	}

	public void setPeek(char peek) {
		this.peek = peek;
	}

}
