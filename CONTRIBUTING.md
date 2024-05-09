# Contribution Guidelines for Project P232

Welcome to the P232 project! We value your contributions and aim to make this process as clear and straightforward as possible. Please follow these guidelines to ensure consistency and quality in our project’s development.

## Branch Naming
- When adding new features or making significant changes, please use the following naming convention for branches:
  ```
  feat/<feature-name>
  ```
  For example: `feat/matrix-multiplication`


- You might also need to fix some problem related with a feature, then you should use following naming:
  ```
  fix/<feature-name>
  ```
  For example: `fix/reduction-operations`
## Code Contributions
### Header Files
- **Header files** must be comprehensive. They should include:
  - Detailed descriptions of the function's purpose.
  - Annotations for each parameter, describing its role.
  - Clear definition of what the function returns.

  Example:
  ```c
  // Initializes a 1D array with default values
  // @param arr: The array to initialize
  // @param size: Number of elements in the array
  // @return void
  void initArray(int* arr, int size);
  ```

### Implementation Files
- **Implementation files** should have a brief comment at the top of each function describing what it does.

  Example:
  ```c
  // Initializes elements of the array to zero
  void initArray(int* arr, int size) {
      for (int i = 0; i < size; i++) {
          arr[i] = 0;
      }
  }
  ```

## Testing Your Code

Before submitting your pull request, it is crucial to ensure that your code is thoroughly tested. This helps to maintain the high quality of our codebase and reduces the likelihood of introducing bugs. Follow these steps to test your code:

1. **Local Testing**:
  - Run your code in your local development environment to make sure it performs as expected.
  - Use the provided test cases or write your own to cover new functionality.

2. **Automated Testing**:
  - If applicable, ensure that all automated tests pass.
  - Update or add new tests if you are introducing new features or making substantial changes to existing functionality.

By following these testing protocols, you help ensure that your contributions are reliable and ready for integration into our main codebase.

## Pull Requests
- Please ensure your code adheres to the existing coding standards of the project.
- Include comments in your code where necessary to explain complex logic.
- Pull Requests (PRs) should be made to the `main` branch and must be reviewed by at least one team member before merging.
- Ensure that your PR title and description clearly state what changes are included and why they are necessary.

## Reporting Issues
- When reporting issues, be clear and concise in your description.
- Include steps to reproduce the problem and screenshots if applicable.

We appreciate your effort in following these guidelines and look forward to seeing your contributions. Thanks!
