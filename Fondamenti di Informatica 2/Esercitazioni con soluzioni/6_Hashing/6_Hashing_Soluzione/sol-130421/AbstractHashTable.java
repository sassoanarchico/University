import java.util.Random;
import java.util.ArrayList;

public abstract class AbstractHashTable {
	private int capacity; // dim. tabella
	private int n = 0; // numero di entry nella tabella
	private int prime; // numero primo
	private long a, b; // coefficienti per MAD
	private double maxLambda; // fattore di carico massimo
	
	// La classe Entry --> coppie (chiave, valore)
	class Entry {	
		private String key;
		private int value;
		public Entry(String k, int v) {
			key = k;
			value = v;
		}
		public String getKey() {
			return key;
		}
		public int getValue() {
			return value;
		}
		public void setValue(int v) {
			value = v;
			return;
		}
		public String toString() {
			return "(" + getKey() + ", " + Integer.toString(getValue()) + ")";
		}
	}
	
	// Costruttori
	public AbstractHashTable(int cap, int p, double lambda) {
		capacity = cap;
		prime = p;
		maxLambda = lambda;
		Random gen = new Random();
		a = gen.nextInt(prime) + 1;
		b = gen.nextInt(prime);
		createTable();
	}
	public AbstractHashTable(int cap, int p) {
		this(cap, p, 0.5); // massimo fattore di carico predefinito
	}
	public AbstractHashTable(int cap) {
		this(cap, 109345121); // primo predefinito
	}
	public AbstractHashTable() {
		this(5); // capacità predefinita
	}
	
	// Metodi ausiliari privati comuni
	protected int hashFunction(String k) { // implementa la funzione hash (hash code + compressione)
		return 	(int) (Math.abs(k.hashCode()*a + b)%prime)%capacity;
	}
	protected void resize(int newCap) { // Aggiorna dimensione tabella hash	
		ArrayList<Entry> buffer = new ArrayList<> (n);
		for (Entry e: entrySet())
			buffer.add(e);
		capacity = newCap;
		createTable(); // la capacità è stata modificata
		n = 0;
		for (Entry e: buffer)
			put(e.key, e.value);
	}
		
	// Metodi comuni
	public boolean isEmpty() { // restituisce true se tabella vuota
		return n == 0;
	}
	
	public int size() { // restituisce il numero di chiavi presenti
		return n;
	}
	
	public int getCapacity() { // restituisce la capacità
		return capacity;
	}
	
	public void incSize() { // incrementa n
		n++;
	}
	
	public void decSize() { // decrementa n
		if (n > 0)
			n--;
	}
	
	public double getMaxLambda() { // restituisce valore del max. fattore di carico
		return maxLambda;
	}
	
	public void print() {
		if (isEmpty()) {
			System.out.println("[]");
			return;
		}
		String s = "["; // Almeno una coppia presente
		for (Entry e: entrySet()) 
			s = s + e.toString() + ",";
		s = s.substring(0, s.length() - 1) + "]";
		System.out.println(s);
	}
	
	// Metodi astratti da implementare nelle sottoclassi
	protected abstract void createTable(); // inizializza la tabella hash
	public abstract int get(String k); // restituisce il valore associato alla chiave k
	public abstract int put(String k, int value); // inserisce un coppia
	public abstract int remove(String k); // rimuove la coppia con chiave k
	public abstract Iterable<Entry> entrySet(); // restituisce un Iterable contentente tutte le coppie presenti
		
}
