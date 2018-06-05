package lexer;
/*
 * 浮点数类，TAG为REAL，但输出时仍为NUM Token
 */
public class Real extends Token {
	public final float value;

	public Real(float v) {
		super(Tag.REAL);
		value = v;
	}

	public String toString() {
		return "" + value;
	}
}
