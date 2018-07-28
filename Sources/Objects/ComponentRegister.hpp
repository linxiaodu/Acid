#pragma once

#include <memory>
#include "IComponent.hpp"

namespace acid
{
	/// <summary>
	/// A class that holds registerd components.
	/// </summary>
	class ACID_EXPORT ComponentRegister
	{
	private:
		typedef std::function<std::shared_ptr<IComponent>()> ComponentCreate;

		std::map<std::string, ComponentCreate> m_components;
	public:
		/// <summary>
		/// Creates a new component register.
		/// </summary>
		ComponentRegister();

		/// <summary>
		/// Deconstructor for the component register.
		/// </summary>
		~ComponentRegister();

		/// <summary>
		/// Registers a component with the register.
		/// </summary>
		/// <param name="update"> The components update type. </param>
		/// <param name="name"> The components name. </param>
		/// <param name="T"> The components type. </param>
		template<typename T>
		void RegisterComponent(const std::string &name)
		{
			if (m_components.find(name) != m_components.end())
			{
				fprintf(stderr, "Component '%s' is already registered!\n", name.c_str());
				return;
			}

			m_components.emplace(name, ComponentCreate([]() -> std::shared_ptr<IComponent>
			{
				return std::dynamic_pointer_cast<IComponent>(std::make_shared<T>());
			}));
		}

		/// <summary>
		/// Deregisters a component.
		/// </summary>
		/// <param name="name"> The components name. </param>
		void DeregisterComponent(const std::string &name);

		/// <summary>
		/// Gets a component create object from the register.
		/// </summary>
		/// <param name="name"> The component name to get. </param>
		/// <returns> The component create object. </returns>
		ComponentCreate GetComponentCreate(const std::string &name);

		/// <summary>
		/// Creates a new component from the register.
		/// </summary>
		/// <param name="name"> The component name to create. </param>
		/// <returns> The new component. </returns>
		std::shared_ptr<IComponent> CreateComponent(const std::string &name);
	};
}