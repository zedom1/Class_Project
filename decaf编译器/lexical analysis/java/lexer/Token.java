package lexer;
/*
 * Token类，作为其它类的父类，拥有一个带参的构造函数和toString方法
 * 重写的toString方法用于最后输出token和value对
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
