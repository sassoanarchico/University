public class Labirinto {

	private static enum Cella { VUOTA, PIENA }; 

	private int n; 
    private Cella m[][]; 
    private boolean marcata[][]; 
   
    public Labirinto(int n) {
    	this.n = n; 
        m = new Cella [n][n];
        marcata = new boolean [n][n]; 
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				m[i][j] = Cella.VUOTA;
				marcata[i][j] = false; 
			}
    }
	
	public void setPiena(int r, int c){
		if(r < 0 || r >= n || c < 0 || c >= n)
			throw new IndexOutOfBoundsException(); 
        m[r][c] = Cella.PIENA; 
    }
	
	private boolean uscita(int r, int c){
        if (r == n-1 && c == n-1)
			return true;
		
		return false;
    }
	
	public boolean percorribile(int r, int c){
        if (r >= n || r < 0 ||
			c >= n || c < 0)
			return false;

		return m[r][c] == Cella.VUOTA && !marcata[r][c]; 
    }
	
	private boolean uscitaRaggiungibileDa(int r, int c){
		if (!percorribile(r,c))
			return false;
		
		marcata[r][c] = true; // marca la cella come gia' esplorata nel percorso attuale
		if (uscita(r, c)) 
			return true;

        for (int i = r+1; i >= r-1; i--) {
        	for (int j = c+1; j >= c-1; j--) {
				if (i != r && j != c)
					continue; // i movimenti in diagonale non sono consentiti
				if (i == r && j == c)
					continue; // ignora il "movimento" nullo
				if (uscitaRaggiungibileDa(i,j)) 
					return true;
            }
		}
		
		marcata[r][c] = false; // la cella non si e' rivelata utile al raggiungimento dell'uscita 
		return false;
    }
	
	public boolean risolvibile(){
		return uscitaRaggiungibileDa(0,0);
	}

    public String toString() {
		int  d = 0;
		char c = ' ';
		char descrizione[] = new char[n*(n+1)];
		
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
				if(m[i][j]==Cella.PIENA)
					c = '#';
				if(m[i][j]==Cella.VUOTA && !marcata[i][j])
					c = '.'; 
				if(m[i][j]==Cella.VUOTA && marcata[i][j])
					c = '+'; 

				descrizione[d++] = c;
			}
			descrizione[d++] = '\n';
        }
        return new String(descrizione);
    }
}
