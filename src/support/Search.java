package support;

public class Search {

	
	public static double editDistance(String str1,String str2) {
		int m = (str1).length()+1;
		int n = (str2).length()+1;
		int [][] matrix = new int[m][n];
		for(int i=0; i<n; i++)
			matrix[0][i] = i;
		for(int i=0; i<m; i++)
			matrix[i][0] = i;
		for(int i=1; i<m; i++)
			for(int j=1; j<n; j++)
				matrix[i][j] = Math.min(Math.min(matrix[i-1][j]+1,matrix[i][j-1]+1), matrix[i-1][j-1])+( str1.charAt(i-1) ==str2.charAt(j-1)?0:1) ;
		return (1.0/(matrix[m-1][n-1]+1));
	}

	public static double lcs(String str1,String str2) {
		int m = (str1).length()+1;
		int n = (str2).length()+1;
		int maxn = 0;
		int [][] matrix = new int[m][n];
		for(int i=1; i<m; i++)
			for(int j=1; j<n; j++) {
				matrix[i][j] = ( str1.charAt(i-1)!=str2.charAt(j-1)?0: matrix[i-1][j-1]+1);
				maxn = (maxn>matrix[i][j]?maxn:matrix[i][j]);
			}
		return (maxn*1.0/m);
	}
	
	public static double getScore(String str1, String str2) {
		if(str1.length()<2)
			return lcs(str1,str2)*2;
		else
			return 0.5*editDistance(str1,str2) + lcs(str1,str2)*0.9;
		
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
