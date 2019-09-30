#include "../includes/runtime.hpp"
#include "../includes/memory.hpp"
#include "../includes/process.hpp"
#include "../includes/data.hpp"
// void* memcpy(void* destination, const void* source, size_t num);
namespace SVM
{
	std::map<Token*, size_t > id_pos_map;
	std::vector<size_t> literary_size;
	void SVM::replace_tag_and_id()
	{
		while (true)
		{
			int id_index;
			int ins_index=0;
			switch (token_stream.this_tag())
			{
			case VAR:
			{
				token_stream.match(VAR);
				file_data.write((char)VAR);
				size_t t = memory.push();
				*token_stream.this_token()->get_add() = t;
				token_stream.match(ID);
				size_t lit_pos = *token_stream.this_token()->get_add();
				size_t lit_length = literary_size[lit_pos];
				file_data.write(lit_length);
				file_data.write(lit_pos);
				break;
			}
			case IST:
			case IADD:
			case ISUB:
			case IMUL:
			case IDIV:
			case RADD:
			case RSUB:
			case RDIV:
			case RMUL:
				file_data.write((char)token_stream.this_tag());
				token_stream.next();
				file_data.write(*token_stream.this_token()->get_add());
				token_stream.next();
				file_data.write(*token_stream.this_token()->get_add());
				token_stream.next();
				file_data.write(*token_stream.this_token()->get_add());
				token_stream.next();
			case IFTRUE:
			case IFFALSE:
			case SADD:
			case SSUB:
			case SMUL:
			case SDIV:
				file_data.write((char)token_stream.this_tag());
				token_stream.next();
				file_data.write(*token_stream.this_token()->get_add());
				token_stream.next();
				file_data.write(*token_stream.this_token()->get_add());
				token_stream.next();
			case GOTO:
			case INC:
			case CALL:
				file_data.write((char)token_stream.this_tag());
				token_stream.next();
				file_data.write(*token_stream.this_token()->get_add());
				token_stream.next();
			default:
				break;
			}
		}
	}
}
namespace ins_func
{
	// integer operation... 
	void iadd(SVM::Param p)
	{
		*(int*)SVM::memory.at(p.p3) = *(int*)SVM::memory.at(p.p1) + *(int*)SVM::memory.at(p.p2);
	}
	void isub(SVM::Param p)
	{
		*(int*)SVM::memory.at(p.p3) = *(int*)SVM::memory.at(p.p1) - *(int*)SVM::memory.at(p.p2);
	}
	void imul(SVM::Param p)
	{
		*(int*)SVM::memory.at(p.p3) = *(int*)SVM::memory.at(p.p1) * *(int*)SVM::memory.at(p.p2);
	}
	void idiv(SVM::Param p)
	{
		*(int*)SVM::memory.at(p.p3) = *(int*)SVM::memory.at(p.p1) / *(int*)SVM::memory.at(p.p2);
	}
	void inc(SVM::Param p)
	{
		(*(int*)SVM::memory.at(p.p1))++;
	}
	// real operation...
	void radd(SVM::Param p)
	{
		*(double*)SVM::memory.at(p.p3) = *(double*)SVM::memory.at(p.p1) + *(double*)SVM::memory.at(p.p2);
	}
	void rsub(SVM::Param p)
	{
		*(double*)SVM::memory.at(p.p3) = *(double*)SVM::memory.at(p.p1) - *(double*)SVM::memory.at(p.p2);
	}
	void rmul(SVM::Param p)
	{
		*(double*)SVM::memory.at(p.p3) = *(double*)SVM::memory.at(p.p1) * *(double*)SVM::memory.at(p.p2);
	}
	void rdiv(SVM::Param p)
	{
		*(double*)SVM::memory.at(p.p3) = *(double*)SVM::memory.at(p.p1) / *(double*)SVM::memory.at(p.p2);
	}

}
