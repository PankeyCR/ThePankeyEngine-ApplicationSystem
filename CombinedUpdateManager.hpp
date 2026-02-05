
#ifndef CombinedUpdateManager_hpp
	#define CombinedUpdateManager_hpp

	namespace pankey{

		namespace ApplicationSystem{

			template<class A, typename... Managers>
			class CombinedUpdateManager : public Managers... {
				public:

				int length() const override {
					int total = 0;
					int dummy[] = {0, (total += Managers::length(), 0)...};
					(void)dummy;
					return total;
				}

				void clear() override {
					int dummy[] = {0, (Managers::clear(), 0)...};
					(void)dummy;
				}

				void initialize(A& a_app) override {
					int dummy[] = {0, (Managers::initialize(a_app), 0)...};
					(void)dummy;
				}

				void update(A& a_app, long a_tpc) override {
					int dummy[] = {0, (Managers::update(a_app, a_tpc), 0)...};
					(void)dummy;
				}
			};

		}

	}

#endif
