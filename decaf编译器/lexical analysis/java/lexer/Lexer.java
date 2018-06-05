package lexer;

import java.io.IOException;
import java.util.*;
/*
 * һ���򵥵�������ʵ�ֵĶ���
 * ���Ա���ǰ��ʧ��ʱ�������ַ�
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
 * �ʷ����������壬�������Դ������дʷ�����
 * ��һ����Ϊwords�Ĺ�ϣ����ؼ��֣����ؼ����ַ����Ͷ�Ӧ��TAG��ӳ��
 * �ڼ��ʱ���Է���ؼ���һ���ַ����Ƿ��ڹ�ϣ�����У����ܹ������ж��Ƿ��ǹؼ���
 * reserve�������ϣ������� �ؼ��֡���TAG ��
 * readch������
 * 		���������İ汾������peekд�뵱ǰ�����ַ�
 * 		�������İ汾������һ���ַ��Ͳ���c���Ƚ��ж��Ƿ���ͬ
 * scan�������϶�ȡ�ַ��������ַ����ͽ����жϣ��Ǵʷ�����������Ҫ����
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
		 * ���Կհ׷����Ʊ�������з�
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
		 * ����ע�ͣ�
		 * 	1. ����ע�� //
		 * 	2. ��ע��  / *  * / ������Ƕ�ף�ֻ����һ��/ * �͵�һ��* /���
		 */
		if(peek=='/') {
			queue.enqueue(peek);
			readch();
			if(peek=='/'||peek=='*') {
				queue.dequeue();
				//   ������ע��
				if(peek=='/') {
					while(!readch('\n'));
				}
				//   �����ע��
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
			//  ����ע�ͣ������ǳ��Ż��������ţ������Żָ�������ո�ȡ�����ַ�
			else {
				queue.enqueue(peek);
				peek=queue.dequeue();
			}
		}
		/*
		 * ������������ж��ǵ����ַ����Ǹ��������
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
		 * �����ֽ���ʶ��
		 * ʶ�����
		 * 	1. ���ַ�Ϊʮ���ƺ�ʮ�����ƣ�ʮ��������0x��0X��ͷ
		 * 	2. �ɴ���С���㣬С�������Բ���������
		 * 	3. �ɴ���ָ��E��e�� ��ɽ� '+' '-'�������ָ����������������һ��ʮ�������֣��ɴ���С��
		 * 	4. С����ǰ����������
		 *  
		 *  ���ܵ��ƥ��ģʽ��  0 x num1 . num2 E num3 . num4
		 */
		if (Character.isDigit(peek)) {
			boolean real=false;
			int nega=1;
			int v = 0;
			// �����������ֲ��֣�10���ƣ�
			do {
				v = 10 * v + Character.digit(peek, 10);
				readch();
			} while (Character.isDigit(peek));	
			if (peek != '.' && peek!= 'E'&& peek!= 'e'&& peek!= 'x'&& peek!= 'X')
				return new Num(v);
			// �����������ֲ��֣�16���ƣ�
			if(v==0 && (peek=='X'||peek=='x')) {
				readch();
				do {
					v = 16 * v + Character.digit(peek, 16);
					readch();
				} while (Character.isDigit(peek)||(peek<='f'&&peek>='a'));
			}
			if (peek != '.' && peek!= 'E'&& peek!= 'e')
				return new Num(v);
			// ����С������
			float x = v;
			if(peek=='.') {
				x = getReal(v);
				real=true;
			}
			if (peek!= 'E'&& peek!= 'e')
				return real==false?new Num(v):new Real(x);
			// ����ָ������
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
		 * ʶ���ʶ����ʶ�����
		 * 	1. �ɰ���Ӣ���ַ�����Сд�������֡��»���
		 * 	2. ������Ӣ���ַ���ͷ
		 * 	3. ��Сд����
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
		 * ʶ���ַ�����ʶ�����
		 * 	1. ��˫���ſ�ͷ����˫���Ž�β��һ��˫�����ڳ���˫���źͻ��з�֮��ľ���Ϊ�ַ���
		 * 	2. δ�����ַ���������Ч����һ�в���Ϊ��һ���ַ����ĺ���
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
