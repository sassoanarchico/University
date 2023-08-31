import java.util.LinkedList;
import java.util.ArrayList;

public class ChainHashTable extends AbstractHashTable {
	// Un array di LinkeList per le liste di trabocco
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
	protected void createTable() {
		table = (LinkedList<Entry>[]) new LinkedList[getCapacity()];
		return;
	}
	public int get(String k) {
		// Da implementare
		if (size() == 0)
			return -1;
		int i = hashFunction(k);
		if (table[i] == null)
			return -1;
		for (Entry e: table[i])
			if (e.getKey().equals(k))
				return e.getValue();
		return -1;
	}
	public int put(String k, int value) {
		int old = -1; // vecchio valore o -1 se chiave assente
		int c = getCapacity();
		if (size() + 1 > c*getMaxLambda())
			resize(2*c - 1);
		int i = hashFunction(k);
		if (table[i] == null) {
			table[i] = new LinkedList<Entry>(); 
			table[i].addLast(new Entry(k, value));
			incSize();
		}
		else {
			for (Entry e: table[i]) 
				if (k.equals(e.getKey())) {
					old = e.getValue();
					e.setValue(value);
				}
			if (old == -1) {
				table[i].addLast(new Entry(k, value));
				incSize();
			}
		}
		return old;
	}
	public int remove(String k) {
		if (isEmpty())
			return -1;
		int i = hashFunction(k);
		if (table[i] == null)
			return -1;
		for (Entry e: table[i])
			if (e.getKey().equals(k)) {
				int old = e.getValue();
				table[i].remove(e);
				decSize();
				if (table[i].size() == 0)
					table[i] = null;
				return old;
			}
		return -1;
	}
	public Iterable<Entry> entrySet() {
		LinkedList<Entry> pairs;
		if (isEmpty())
			return null;
		pairs = new LinkedList<Entry>();
		for (int i = 0; i < table.length; i++)
			if (table[i] != null)
				for (Entry e: table[i])
					pairs.addLast(e);
		return pairs;
	}

}


