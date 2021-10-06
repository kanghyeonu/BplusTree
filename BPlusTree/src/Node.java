import java.util.*;

public abstract class Node {
	protected Node parent;
	protected ArrayList<String> Keys;
	protected int Degree;
	
	public int getKeysize() {
		return this.Keys.size();
	}
	//����
	abstract void insert(BPTree bplus ,String data);
	abstract void PreOrder();
	abstract Node getRoot(Node node);
	//abstract Node delete(String data);
	
}

class LeafNode extends Node{
	private LeafNode next;
	//private Map<String, ArrayList<String>> data;
	
	LeafNode(int Degree){
		this.parent = null;
		this.next = null;
		Keys = new ArrayList<String>(Degree-1);
		//data = new HashMap<String, ArrayList<String>>();
		
		this.Degree  = Degree;
	}
	
	//������忡���� ����
	@Override
	public void insert(BPTree bplus, String data) {
		//ó���� �����ʹ� Keys�� �߰�
		if(this.Keys.indexOf(data) < 0)
		{
			this.Keys.add(data);
			Collections.sort(this.Keys);
		}
		//�ߺ������ʹ� Ű�� ��������
		
		//���� ���� ������ dataó��
		
		//���� �� ������ �Ͼ�� ���̽� 
		//case: split in leafnode
		if( this.getKeysize() == this.Degree) {
			//�켱 �� �ɰ��� ���� �� ������� ���� �� Ű�� ������ ����
			LeafNode newLeaf = new LeafNode(this.Degree);
			newLeaf.Keys.addAll(this.Keys);
			for(int i = 0; i < 3; i++) {
				this.Keys.remove(0);	//ū �������
				newLeaf.Keys.remove(3);	//���� �� �����
			}
			//���ø� �� case1: parent�� ������
			// ���� ��� ������ ����
			if(this.parent == null)
			{
				InternalNode newparent = new InternalNode(Degree);
				newparent.Keys.add(this.Keys.get(0));	//�θ� ��忡 �� ���� ���� ����� �������� ��
				//���� ���� ���� ������ ���ʷ� ����
				newparent.childs.add(newLeaf);
				newparent.childs.add(this);	
				this.parent = newLeaf.parent = newparent;	//�θ��� ����
				bplus.setRoot(getRoot(this)); //��Ʈ����
			}
			//���ø� �� case2: parent�� ������
		}
	}
	
	@Override
	void PreOrder() {
		for(int i = 0; i < this.Keys.size(); i++) {
			System.out.print(this.Keys.get(i)+" ");
		}
	}

	@Override
	Node getRoot(Node node) {
		if(this.parent == null)
			return this;
		
		return this.parent.getRoot(node);
	}

}
//���ͳ� ��忡���� ���� pointer ����
class InternalNode extends Node{
	protected ArrayList<Node> childs; //��� ������
	
	InternalNode(int Degree){
		this.parent = null;
		Keys = new ArrayList<String>(Degree-1);
		childs = new ArrayList<Node>(Degree);
		this.Degree = Degree;
	}
	@Override
	void insert(BPTree bplus, String data) {
		int index = 0;
		//index�� �̿��ؼ� child�� ����
		for(index = 0; index < this.Degree-1;) {
		//���� �����Ͱ� ��� ���� �ش� �ε�����ġ�� �����ͺ��� ũ�� �ε��� ����
			if(data.compareTo(this.Keys.get(index)) < 0)
				index++;
			//���ٸ� ����
			else if(data.compareTo(this.Keys.get(index)) == 0)
				return;
			//�´���ġ��� 
			else
				break;
		}
		this.childs.get(index).insert(bplus, data);	
	}
	@Override
	void PreOrder() {
		for(int i = 0; i < this.Keys.size(); i++) {
			System.out.print(this.Keys.get(i)+" ");
		}
		System.out.println();
		for(int i = 0; i < this.childs.size(); i++) {
			this.childs.get(i).PreOrder();
		}
	}
	@Override
	Node getRoot(Node node) {
		if(this.parent == null)
			return this;
		return this.parent.getRoot(node);
	}
}