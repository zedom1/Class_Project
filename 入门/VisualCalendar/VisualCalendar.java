package VisualCalendar;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Scanner;
 /**
  * JAVA��ѧ����
  * ����Calendar���Date�����򵥵Ŀ��ӻ�����
  * ���ݸ�����ʽ���ַ������ɵ��µ�����
  * @author Zedom
  *
  */
public class VisualCalendar {

		
		public static void main(String[] args) {
			System.out.println("���������� (����ʽ�� 2017-09-10)");
			Scanner in = new Scanner(System.in);
			String tem = in.next();
			DateFormat df = new SimpleDateFormat("yyyy-MM-dd");
			try {
				Date date = df.parse(tem);
				Calendar calendar = new GregorianCalendar();
				calendar.setTime(date);
				int aimDate=calendar.get(Calendar.DATE);
				calendar.set(Calendar.DATE, 1);
				int first = calendar.get(Calendar.DAY_OF_WEEK)-1;
				int maxn=calendar.getActualMaximum(Calendar.DATE);
				System.out.println("��\tһ\t��\t��\t��\t��\t��");
				int j=0;
				for( ; j<first ; j++)
					System.out.print(" \t");
				for(int i = 1; i<=maxn; i++) {
					j++;
					System.out.print(i);
					if(i==aimDate)
						System.out.print("*");
					System.out.print('\t');
					if(j%7==0)
						System.out.println("");
				}
			} catch (ParseException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
}
