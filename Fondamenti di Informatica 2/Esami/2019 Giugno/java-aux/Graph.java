import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.HashMap;

public class Graph<V> {

    private LinkedList<GraphNode<V>> nodes;
    private int n_nodes;
    private int n_edges;

    public Graph () {
        this.nodes = new LinkedList<GraphNode<V>>();
    }
    
    public int getNoNodes() {
		return n_nodes;
	}
	
	public int getNoEdges() {
		return n_edges;
	}

    @SuppressWarnings("unchecked")
	public List<GraphNode<V>> getNodes() {
    	List<GraphNode<V>> ret = new LinkedList<>();
    	for(GraphNode<V> n : this.nodes) {
    		try {
				ret.add((GraphNode<V>) n.clone());
			} catch (CloneNotSupportedException e) {
				e.printStackTrace();
			}
    	}
        return (List<GraphNode<V>>) ret;
    }

    @SuppressWarnings("unchecked")
	public List<GraphNode<V>> getNeighbors(GraphNode<V> n){
    	List<GraphNode<V>> ret = new LinkedList<>();
    	for(GraphNode<V> edge : n.outEdges) {
    		try {
				ret.add((GraphNode<V>) edge.clone());
			} catch (CloneNotSupportedException e) {
				e.printStackTrace();
			}
    	}
        return (List<GraphNode<V>>) ret;
    }

    public GraphNode<V> addNode(V value) {
        GraphNode<V> n = new GraphNode<V>();
        n.value = value;
        n.outEdges = new LinkedList<GraphNode<V>>();
        n.state = GraphNode.Status.UNEXPLORED;
        n.timestamp = 0;
        for(GraphNode<V> node : this.nodes) {
        	if(node.value.equals(value))
        		return node;
        }
        this.nodes.add(n);
        this.n_nodes++;
        return n;
    }

    public void addEdge(GraphNode<V> s, GraphNode<V> t) {
		/* DA IMPLEMENTARE */
    }

    public V getNodeValue(GraphNode<V> n) {
        return n.value;
    }
    
    public void removeEdge(GraphNode<V> v1, GraphNode<V> v2){
		if (v1.outEdges.contains(v2))
			v1.outEdges.remove(v2);
		if (v2.outEdges.contains(v1))
			v2.outEdges.remove(v1);
		this.n_edges--;
		return;
    }
    
    
    public void removeNode(GraphNode<V> v){
    	if(this.nodes.contains(v)) {
			LinkedList<GraphNode<V>> toRemove = new LinkedList();
			Iterator<GraphNode<V>> it = v.outEdges.iterator();
			while(it.hasNext()) 
				toRemove.add(it.next());
			for (GraphNode<V> e: toRemove) {
	    		this.removeEdge(v, e);
	    	}
    	}
    	this.nodes.remove(v);
    	this.n_nodes--;
    }
    
    @Override
    public String toString(){
    	HashMap<GraphNode<V>, GraphNode.Status> savedStatus = new HashMap<>();
    	for(GraphNode<V> node : this.nodes) {
    		savedStatus.put(node, node.state);
    		node.state = GraphNode.Status.UNEXPLORED;
    	}
    	
    	StringBuffer toRet = new StringBuffer();
    	toRet.append(this.n_nodes + " " + this.n_edges + "\n");
    	for(GraphNode<V> node : this.nodes) {
    		if(node.state == GraphNode.Status.UNEXPLORED)
    			DFSprintEdges(node, toRet);
    	}
    	
    	for(GraphNode<V> node : this.nodes) {
    		node.state = savedStatus.get(node);
    	}
    	return toRet.toString();
    }

    private void DFSprintEdges(GraphNode<V> node, StringBuffer str) {
    	if(node.state != GraphNode.Status.UNEXPLORED)
    		return;
    	node.state = GraphNode.Status.EXPLORING;
    	for(GraphNode<V> e : node.outEdges) {
			if(e.state == GraphNode.Status.UNEXPLORED)
				str.append(node.value + " " + e.value + "\n");
    	}
    	for(GraphNode<V> e : node.outEdges) {
    		if(e.state == GraphNode.Status.UNEXPLORED)
    			DFSprintEdges(e, str);
    	}
    	node.state = GraphNode.Status.EXPLORED;
	}
	
	
    public static <V> Graph<V> readFF(File input){
    	Graph<V> toRet = new Graph<>();
    	try {
			BufferedReader br = new BufferedReader(new FileReader(input));
			String firstLine = br.readLine();
			StringTokenizer tok = new StringTokenizer(firstLine);
			int v = Integer.parseInt(tok.nextToken());
			int e = Integer.parseInt(tok.nextToken());
			for(int i = 0; i< e; i++) {
				tok = new StringTokenizer(br.readLine());
				while(tok.hasMoreTokens()) {
					GraphNode<V> v1 = toRet.addNode((V) tok.nextToken());
					GraphNode<V> v2 = toRet.addNode((V) tok.nextToken());
					toRet.addEdge(v1, v2);
				}
			}
			br.close();
			if(toRet.n_nodes < v) {
				int rem = v - toRet.n_nodes;
				int name = e + 1;
				for(int i = 0; i<rem; name++, i++) {
					toRet.addNode((V) (name + ""));
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return toRet;
    }

}
