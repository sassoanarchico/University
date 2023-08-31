import java.util.LinkedList;
import java.util.ArrayList;

public class ChainHashTable extends AbstractHashTable {
	// Un array di LinkedList per le liste di trabocco 
	// L'array table implementa la tabella hash
	private LinkedList<Entry> [] table;
	
	// Costruttori
	public ChainHashTable(int cap, int p, double lambda) {
		super(cap, p, lambda);
	}
	public ChainHashTable(int cap, int p) {
		super(cap, p); // massimo fattore di carico predefinito
	}
	public ChainHashTable(int cap) {
		super(cap); // primo predefinito
	}
	public ChainHashTable() {
		super(); // capacità predefinita
	}
	
	// Metodi non implementati in AbstractHashTable

	// Inizializza una tabella hash vuota secondo i parametri passati al costruttore
	protected void createTable() {
		return;
	}

	// Restituisce il valore (intero) associato alla chiave k
	// Restituisce -1 se la chiave è assente
	public int get(String k) {
		return -1;
	}
	
	// Aggiorna il valore associato alla chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int put(String k, int value) {
		return -1;
	}
	
	
	// Rimuove la coppia con chiave k
	// Restituisce il vecchio valore o -1 se la chiave non è presente
	public int remove(String k) {
		return -1;
	}
	
	// Restituisce un oggetto Iterable contenente tutte le coppie presenti
	// nella tabella hash
	public Iterable<Entry> entrySet() {
		return null;
	}

}


