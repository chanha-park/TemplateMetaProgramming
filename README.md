# TemplateMetaProgramming

새로운 클래스를 만드는 것은, 새로운 타입을 만드는 것이기도 하다. `Zero`에 해당하는 타입을 만들고, `어떤 타입 T의 다음 타입`을 만들 수 있으면 정적타입으로 수 체계를 따라할 수 있다.

비슷하게 `어떤 타입 T, U을 더한 타입`(대수적타입의 합타입과는 다르다)을 만드는 식으로 사칙연산을 구현할 수 있다. 나눗셈은 유리수로 구현하기 힘들 듯해서 정수범위의 몫으로 구현했는데... 생각보다 복잡해져서 `Eval`을 이용한 `Is_Less`클래스를 만들어 구현해두었다.

`Eval` 클래스는 헬퍼 클래스로, 각 타입을 static const int 타입으로 변환해준다. 현재 나눗셈을 제외하곤 구현상 필요한 부분은 아니지만, 런타임에 출력으로 값을 확인할 때 필요하다.

`T + Succ(U) = Succ(T) + U`, `T * Succ(U) = T * U + U`와 같은 식들은 이전에 [natural number game](https://github.com/chanha-park/naturalNumberGame)에서 유도했던 결과들을 이용했다.
