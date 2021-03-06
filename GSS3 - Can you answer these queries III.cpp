#include <bits/stdc++.h>

#define ll long long

using namespace std;

struct segtree{
	ll prefix_max_sum,suffix_max_sum,max_sum,sum;

	void assign_leaf(ll value)
	{
		prefix_max_sum=suffix_max_sum=max_sum=sum=value;
	}

	void merge(segtree& left,segtree& right)
	{
		sum=left.sum+right.sum;
		prefix_max_sum=max(left.prefix_max_sum,left.sum+right.prefix_max_sum);
		suffix_max_sum=max(right.suffix_max_sum,right.sum+left.suffix_max_sum);
		max_sum=max(prefix_max_sum,max(suffix_max_sum,max(left.max_sum,max(right.max_sum,left.suffix_max_sum+right.prefix_max_sum))));
	}

	ll get_value()
	{
		return max_sum;
	}
};

ll arr[500005],n;

segtree nodes[1000005];

segtree get_value(ll st_index,ll left,ll right,ll l,ll r)
{
	//cout<<"Index "<<st_index<<" Left is  "<<left<<" Right is "<<right<<endl;
	if(left==l && right==r)
	{
		return nodes[st_index];
	}
	ll mid=left+(right-left)/2;
	if(l>mid)
	{
		return get_value(2*st_index+1,mid+1,right,l,r);
	}
	if(r<=mid)
	{
		return get_value(2*st_index,left,mid,l,r);
	}
	segtree left_result=get_value(2*st_index,left,mid,l,mid);
	segtree right_result=get_value(2*st_index+1,mid+1,right,mid+1,r);
	segtree result;
	result.merge(left_result,right_result);
	return result;
}

void query_tree(ll l,ll r)
{
	segtree result=get_value(1,1,n,l,r);
	printf("%lld\n",result.get_value());
}

void build_tree(ll st_index,ll left,ll right)
{
	//cout<<"Index "<<st_index<<" Left is  "<<left<<" Right is "<<right<<endl;
	if(left==right)
	{
		nodes[st_index].assign_leaf(arr[left]);
		return;
	}
	ll mid=left+(right-left)/2;
	build_tree(2*st_index,left,mid);
	build_tree(2*st_index+1,mid+1,right);
	nodes[st_index].merge(nodes[2*st_index],nodes[2*st_index+1]);
}

void update_value(ll st_index,ll left,ll right,ll index,ll value)
{
	if(left==right)
	{
		arr[left]=value;
		nodes[st_index].assign_leaf(value);
		return;
	}
	ll mid=left+(right-left)/2;
	if(index<=mid)
	{
		update_value(2*st_index,left,mid,index,value);
	}
	else
	{
		update_value(2*st_index+1,mid+1,right,index,value);
	}
	nodes[st_index].merge(nodes[2*st_index],nodes[2*st_index+1]);
}

void update_tree(ll index,ll value)
{
	update_value(1,1,n,index,value);
}

int main()
{
	ll m,i,j,k;
	scanf("%lld",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&arr[i]);
	}
	build_tree(1,1,n);
	scanf("%lld",&m);
	while(m--)
	{
		ll a,b,c;
		scanf("%lld%lld%lld",&a,&b,&c);
		if(a==1)
			query_tree(b,c);
		else
			update_tree(b,c);
	}
	return 0;
}