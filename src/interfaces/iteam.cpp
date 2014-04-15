#include "../interfaces/igroup.cpp"

class ITeam {
	public:
		virtual IGroup *get_groups();
		virtual void add_group(IGroup *group);
		virtual void del_group(IGroup *group);

		virtual int get_color();
	private:
		IGroup *groups;
		int color;
};
