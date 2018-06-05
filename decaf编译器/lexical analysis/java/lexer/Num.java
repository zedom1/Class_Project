package lexer;
/*
 * 整数类，与NUM类TOKEN相对应
 */
public class Num extends Token {

	public final int value;

	public Num(int v) {
		super(Tag.NUM);
		value = v;
	}

	public String toString() {
		return "" + value;
	}

}
