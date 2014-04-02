#ifndef _ITEM_BASE_H_
#define _ITEM_BASE_H_

class ItemBase {
public:
	enum Type {
		INTEGER = 1, FLOAT = 2, STRING = 3, DATE = 4, TIME = 5
	};

protected:
	//bool isNull;
	Type itemType;

public:
	//virtual void SetIsNull(bool null)=0;
	virtual void SetType(Type type) = 0;
	//virtual void PrintData()=0;
	Type GetType();
	//bool IsNull();
};

#endif
