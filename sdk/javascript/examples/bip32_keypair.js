#!/usr/bin/env node

//
// Shows how to use Bip32 interface to derive keys.
//
// note: this example is *not* generating keys compatible with wallet
//

const symbolSdk = require('../src/index');

(() => {
	const deriveKey = (rootNode, facade, change, index) => {
		const path = [44, facade.constructor.BIP32_COIN_ID, 0, change, index];

		const childNode = rootNode.derivePath(path);
		const childKeyPair = facade.constructor.bip32NodeToKeyPair(childNode);

		console.log(` PATH: [${path.join(', ')}]`);
		console.log(` * private key: ${childKeyPair.privateKey}`);
		console.log(` *  public key: ${childKeyPair.publicKey}`);

		const address = facade.network.publicKeyToAddress(childKeyPair.publicKey);
		console.log(` *     address: ${address}`);
		console.log('');
	};

	const facade = new symbolSdk.facade.SymbolFacade('testnet');

	const bip = new symbolSdk.Bip32(facade.BIP32_CURVE_NAME);
	const rootNode = bip.fromMnemonic(
		'cat swing flag economy stadium alone churn speed unique patch report train',
		'correcthorsebatterystaple'
	);

	[0, 1].forEach(change => {
		[0, 1, 2].forEach(index => {
			deriveKey(rootNode, facade, change, index);
		});
	});
})();
