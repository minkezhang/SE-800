#include <vector>

/**
 * TODO: still need to include featurese from Justin's phone
 */

class ICube {
	public:
		virtual int get_id();
		virtual std::vector<float> get_dim();

	private:
		int id;
		std::vector<float> dim;
};
