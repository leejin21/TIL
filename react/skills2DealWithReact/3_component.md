# 3.1 클래스형 컴포넌트

클래스형 컴포넌트: 이후 배울 state 기능 및 라이프사이클 기능을 사용할 수 있다는 것과 임의 메서드를 정의할 수 있음(↔ 함수형 컴포넌트)

# 3.3 props

## defaultProps

_그렇게 많이 쓰는 걸 본 적이 없지만 알아두면 쓸 데가 있을 듯?_

-   원래
-   default props 예제 1
-   default props 예제 2

## destructuring assignment(비구조화 할당)

-   책에서
-   조오오오금 심화 스킬

## propTypes를 통한 props 검증

propTypes로 props 검증하기: for debugging

-   예제

    ```jsx
    import PropTypes from "prop-types";

    MyCompoent.propTypes = {
        name: PropTypes.String,
    };
    ```

크롬 개발자 도구> 콘솔에 경고 메세지를 볼 수 있음.

단, 지정해 준 PropTypes와 달라도 render는 됨.

## isRequired를 사용해 필수 propTypes를 설정

-   예제

    ```jsx
    import PropTypes from "prop-types";

    MyCompoent.propTypes = {
        name: PropTypes.String.isRequired,
    };
    ```

❓이제 name에 String Type이 아닌 것이 들어가게 되면 에러 메세지가 뜬다??

자세한 Type에 대한 것은: [https://github.com/facebook/prop-types](https://github.com/facebook/prop-types) 참고하기

++ JOY

## 클래스형 컴포넌트에서 props 사용하기

-   예제

```jsx
render() {
	static defaultProps = {
		name: "기본 이름"
	}
	static propTypes = {
		name: PropTypes.string,
		number: PropTypes.number.isRequired
	}
	const {name, children, number} = this.props;
	return (...);
}
```

# 3.4 state

-   ❓state는 왜 있는 것인가?

props (“properties”의 줄임말) 와 state 는 일반 JavaScript 객체입니다. 두 객체 모두 렌더링 결과물에 영향을 주는 정보를 갖고 있는데, 한 가지 중요한 방식에서 차이가 있습니다. props는 (함수 매개변수처럼) 컴포넌트에 전달되는 반면(컴포넌트에서는 props값 변경 불가) state는 (함수 내에 선언된 변수처럼) 컴포넌트 안에서 관리됩니다.

state가 있어야 컴포넌트에 변경된 값이 감지되고, 1장에서 설명했던 것처럼 리렌더됨(reconciliation 과정).

## 클래스형 컴포넌트의 state

### this.setState에 객체 대신 함수 인자 전달하기

-   예제

```jsx
import React, { Component } from "react";

class Counter extends Component {
    /*
		construnctor(props) {
				super(props);
				this.state = {
					// 이렇게도 가능
					// ...
				}
		}
		*/
    state = {
        number: 0,
        fixedNumber: 0,
    };
    render() {
        const { number, fixedNumber } = this.state;
        return (
            <div>
                <h1>{number}</h1>
                <h1>{fixedNumber}</h1>
                <button
                    onClick={() => {
                        this.setState((prevState, props) => ({
                            // props: Counter의
                            number: prevState.number + 1,
                        }));
                    }}
                >
                    +1
                </button>
            </div>
        );
    }
}

export default Counter;
```

❗ 주의: setState에서 뭘 인자로 넣던 반환하는 객체에 fixedNumber에 대한 정보가 없어도 fixedNumber는 그대로 정보가 유지되는 듯(prevState) 그대로

## 함수형 컴포넌트에서 useState 사용하기

### 배열 비구조화 할당

-   예제

```jsx
const array = [0, 1];
const [a, b] = array;
console.log("a=", a, ", b=", b);
// a=0, b=1
```

### useState 사용하기

-   예제

```jsx
///////////////////////////////////////////////////////
// * IMPORT SECTION

import React, { useState } from "react";

///////////////////////////////////////////////////////
// * MAIN SECTION
const Say = () => {
    const [message, setMessage] = useState("");
    // 배열 비구조화 할당문
    const goWork = () => {
        setMessage((message) => "좋은 아침입니다");
    };
    const offWork = () => {
        setMessage((message) => "먼저 퇴근하겠습니다");
    };
    return (
        <div>
            <button onClick={goWork}>출근</button>
            <button onClick={offWork}>퇴근</button>
            <h1>{message}</h1>
        </div>
    );
};
///////////////////////////////////////////////////////
// * EXPORT SECTION
export default Say;
```

useState()로 반환되는 배열의 첫 요소 ⇒ 현재 상태,

배열의 두번째 요소 ⇒ 현재 상태를 바꿀 수 있는 함수

# 3.5 state를 사용할 때 주의 사항

> 사본 사용하기: 배열의 경우 concat, 객체의 경우 spread 연산자(...)

[Why Immutability is important](https://www.notion.so/Why-Immutability-is-important-542e3dca878b409dab0af5a9ec09ff6b)
