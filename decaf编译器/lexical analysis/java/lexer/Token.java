package lexer;
/*
 * Token�࣬��Ϊ������ĸ��࣬ӵ��һ�����εĹ��캯����toString����
 * ��д��toString��������������token��value��
 */
public class Token {

	public final int tag;

	public Token(int t) {
		tag = t;
	}

	public String toString() {
		return "" + (char) tag;
	}
}
