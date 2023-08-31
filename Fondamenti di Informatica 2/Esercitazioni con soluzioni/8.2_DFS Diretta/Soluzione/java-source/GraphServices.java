import java.util.LinkedList;
import java.util.List;

public class GraphServices<V> {

    public static <V> void sweep(Graph<V> g) {
        // Reset node's status
        g.resetStatus();
        
       
    }

    private static <V> void sweep_aux(Graph g, Graph.Node<V> node) {
        node.state = Graph.Node.Status.EXPLORING;
    }

    private static<V> int DDFS(Graph.Node<V> nd, LinkedList<Graph.Node<V>> ts) {
        if(nd.state == Graph.Node.Status.EXPLORING)
            return 1;
        
        if(nd.state == Graph.Node.Status.EXPLORED)
            return 0;
        
        nd.state = Graph.Node.Status.EXPLORING;
        int ret = 0;
        
        for(Graph.Node<V> cur : nd.outEdges)
            ret += DDFS(cur, ts);
        
        nd.state = Graph.Node.Status.EXPLORED;
        ts.addFirst(nd);
        return ret;
    }

    private static<V> void transposedDFS(Graph.Node<V> nd, LinkedList<Graph.Node<V>> ret) {
        if(nd.state == Graph.Node.Status.EXPLORING)
            return;
        
        if(nd.state == Graph.Node.Status.EXPLORED)
            return;
        
        nd.state = Graph.Node.Status.EXPLORING;
        for(Graph.Node<V> cur : nd.inEdges)
            transposedDFS(cur, ret);
        
        ret.addLast(nd);
        nd.state = Graph.Node.Status.EXPLORED;
    }

    /* SOLUTION ONLY WITH OUT EDGES
    private static<V> void transposedDFS(Graph<V> g, Graph.Node<V> n, LinkedList<Graph.Node<V>> ret) {
        if(n.state != Graph.Node.Status.UNEXPLORED)
            return;
        
        n.state = Graph.Node.Status.EXPLORING;
        for(Graph.Node<V> to : g.getNodes()) {
            for(Graph.Node<V> frm : to.outEdges) {
                if(frm == n)
                    transposedDFS(g, to, ret);
            }
        }
        
        ret.addLast(n);
        n.state = Graph.Node.Status.EXPLORED;
    }
    */

    // This is Kosaraju's algorithm
    public static <V> void strongConnectedComponents(Graph<V> g) {
        // Reset node's status
        g.resetStatus();

        // First DFS
        LinkedList<Graph.Node<V>> stack = new LinkedList<>();
        for(Graph.Node<V> n : g.getNodes()) {
            if(n.state == Graph.Node.Status.UNEXPLORED)
                DDFS(n, stack);
        }

        // Reset node's status
        g.resetStatus();

        // Second DFS on the transposed graph
        for(Graph.Node<V> n : stack) {
            if(n.state == Graph.Node.Status.UNEXPLORED) {
                LinkedList<Graph.Node<V>> ret = new LinkedList<>();
                transposedDFS(n, ret);
                
                System.out.println("Strong connected component:");
                for(Graph.Node<V> cur : ret)
                    System.out.print(cur.value + " ");
                System.out.println("");
            }
        }
    }

    public static <V> void topologicalSort(Graph<V> g) {
        // Reset node's status
        g.resetStatus();

        LinkedList<Graph.Node<V>> ts = new LinkedList<Graph.Node<V>>();
        
        for(Graph.Node<V> nd : g.getNodes()) {
            if(nd.state == Graph.Node.Status.UNEXPLORED) {
                if(DDFS(nd, ts) > 0) {
                    System.out.println("Impossibile ottenere ordine topologico, il grafo non è un DAG");
                    return;
                }
            }
        }

        for(Graph.Node<V> nd : ts)
            System.out.print(nd.value + " ");
        System.out.println("");
    }
}
