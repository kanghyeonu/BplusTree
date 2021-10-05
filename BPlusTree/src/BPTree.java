/*----------------------------------------* 
 * 
 * 6 way B+Tree
 * node 당 child 개수 = 3개 ~ 6개
 * node 당 Key 개수 = 2개 ~ 5개
 * 
 *----------------------------------------*/

public class BPTree {
	private Node root;
	private LeafNode head;
	private int Degree;
	private int min_child, min_Key, max_child, max_key;
	
	BPTree(){
		this.root = null;
		this.head = null;
		this.Degree = 6;
		this.min_child = this.Degree/2;
		this.max_child = this.Degree;
		this.min_Key = this.Degree/2 - 1;
		this.max_key = this.Degree - 1;	
	}
	
	BPTree(int Degree){
		this.root = null;
		this.head = null;
		if(Degree%2 == 0)
			this.Degree = Degree;
		else
			this.Degree = Degree+1;		
		this.min_child = this.Degree/2;
		this.max_child = this.Degree;
		this.min_Key = this.Degree/2 - 1;
		this.max_key = this.Degree - 1;
	}
	
	void insert(String data) {
		this.insert(data, this.Degree);
	}
	
	private void insert(String data, int Degree) {
		//루트가 비어있을때
		if(this.root == null)
		{
			LeafNode newnode = new LeafNode(Degree);
			this.root = newnode;
			this.head = newnode;
			this.root.insert(data, Degree);
			return;
		}
		//트리가 있을 때, 루트부터 순회 후 알맞은 leafnode에 삽입 후 그 leaf노드 반환
		Node temp = this.root.insert(data, this.max_key);;
		
		
		//case 1. 삽입 후 분할이 일어나지 않는 경우
		
		//case 2. 분할이 일어나는 경우
	}
}
